#include "PosixTestClient.h"

#include "EPosixClientSocket.h"
#include "EPosixClientSocketPlatform.h"

#include "Contract.h"
#include "Order.h"

#include <time.h>
#include <sys/time.h>

#if defined __INTEL_COMPILER
# pragma warning (disable:869)
#elif defined __GNUC__
# pragma GCC diagnostic ignored "-Wswitch"
# pragma GCC diagnostic ignored "-Wunused-parameter"
#endif  /* __INTEL_COMPILER */

namespace IB {

const int PING_DEADLINE = 2; // seconds
const int SLEEP_BETWEEN_PINGS = 30; // seconds

PosixTestClient::PosixTestClient()
	: m_pClient(new EPosixClientSocket(this))
	, m_state(ST_CONNECT)
	, m_sleepDeadline(0)
	, m_orderId(0)
{
}

PosixTestClient::~PosixTestClient()
{
}

bool PosixTestClient::connect(const char *host, unsigned int port, int clientId)
{
	// trying to connect
	LOGGER(DEBUG_FLAG, "Connecting to " << "127.0.0.1:7469 clientId: " << clientId);

	bool bRes = m_pClient->eConnect2( host, port, clientId);

	if (bRes) {
		LOGGER(DEBUG_FLAG, "Connected to " << "127.0.0.1:7469 clientId: " << clientId);
	}
	else
		LOGGER(DEBUG_FLAG, "Cannot connect to 127.0.0.1:7469 clientId: " <<  clientId);

	return bRes;
}

void PosixTestClient::disconnect() const
{
	m_pClient->eDisconnect();

	LOGGER(DEBUG_FLAG, "Disconnected");
}

bool PosixTestClient::isConnected() const
{
	return m_pClient->isConnected();
}

void PosixTestClient::processMessages(vector<Option>& vec)
{
	fd_set readSet, writeSet;

	struct timeval tval;
	tval.tv_usec = 0;
	tval.tv_sec = 0;

	time_t now = time(NULL);

	switch (m_state) {
		case ST_PLACEORDER:
			placeOrder(vec);
			break;
		case ST_PLACEORDER_ACK:
			break;
		case ST_CANCELORDER:
			break;
		case ST_CANCELORDER_ACK:
			break;
		case ST_PING:
			reqCurrentTime();
			break;
		case ST_PING_ACK:
			if( m_sleepDeadline < now) {
				disconnect();
				return;
			}
			break;
		case ST_IDLE:
			if( m_sleepDeadline < now) {
				m_state = ST_PING;
				return;
			}
			break;
	}

	if( m_sleepDeadline > 0) {
		// initialize timeout with m_sleepDeadline - now
		tval.tv_sec = m_sleepDeadline - now;
	}

	if( m_pClient->fd() >= 0 ) {

		FD_ZERO( &readSet);
		writeSet = readSet;

		FD_SET( m_pClient->fd(), &readSet);

		if( !m_pClient->isOutBufferEmpty())
			FD_SET( m_pClient->fd(), &writeSet);

		int ret = select( m_pClient->fd() + 1, &readSet, &writeSet, NULL, &tval);

		if( ret == 0) { // timeout
			return;
		}

		if( ret < 0) {	// error
			disconnect();
			return;
		}

		if( FD_ISSET( m_pClient->fd(), &writeSet)) {
			// socket is ready for writing
			m_pClient->onSend();
		}

		if( m_pClient->fd() < 0)
			return;

		if( FD_ISSET( m_pClient->fd(), &readSet)) {
			// socket is ready for reading
			m_pClient->onReceive();
		}
	}
}

//////////////////////////////////////////////////////////////////
// methods
void PosixTestClient::reqCurrentTime()
{
	LOGGER(DEBUG_FLAG, "Requesting Current Time");

	// set ping deadline to "now + n seconds"
	m_sleepDeadline = time( NULL) + PING_DEADLINE;

	m_state = ST_PING_ACK;

	m_pClient->reqCurrentTime();
}

Contract createContract(Option& opt) {
	Contract tempCon;
	tempCon.secType = "OPT";
  tempCon.multiplier = "100";
  tempCon.exchange = "SMART";
  tempCon.currency = "USD";
  tempCon.localSymbol = "";
  if (opt.getOptionType())
  	tempCon.right = "PUT";
  else
  	tempCon.right = "CALL";
  tempCon.symbol = opt.getStockName();

  boost::gregorian::date expDate = boost::gregorian::from_simple_string(opt.getExpirationDate());
  tempCon.expiry = boost::gregorian::to_iso_string(expDate);
  tempCon.strike = opt.getStrikePrice();

  return tempCon;
}

Order createOrder(Option& opt) {
	Order tempOrder;

	tempOrder.action = "BUY";
	tempOrder.totalQuantity = 10;
	tempOrder.orderType = "LMT";
	tempOrder.lmtPrice = opt.getOptionPrice();

	return tempOrder;
}

void PosixTestClient::placeOrder(vector<Option>& vec)
{

	Contract contract1 = createContract(vec[0]);
	Order order1 = createOrder(vec[0]);

	Contract contract2 = createContract(vec[1]);
	Order order2 = createOrder(vec[1]);

	Contract contract3 = createContract(vec[2]);
	Order order3 = createOrder(vec[2]);

	Contract contract4 = createContract(vec[3]);
	Order order4 = createOrder(vec[3]);

	// printf( "Placing Order %ld: %s %ld %s at %f\n", m_orderId, order.action.c_str(), order.totalQuantity, contract.symbol.c_str(), order.lmtPrice);

	m_state = ST_PLACEORDER_ACK;

	m_pClient->placeOrder(m_orderId, contract1, order1);
	m_pClient->placeOrder(m_orderId + 1, contract2, order2);
	m_pClient->placeOrder(m_orderId + 2, contract3, order3);
	m_pClient->placeOrder(m_orderId + 3, contract4, order4);
}

void PosixTestClient::cancelOrder()
{
	LOGGER(DEBUG_FLAG, "Cancelling Order " << m_orderId);

	m_state = ST_CANCELORDER_ACK;
	m_pClient->cancelOrder(m_orderId);
}

///////////////////////////////////////////////////////////////////
// events
void PosixTestClient::orderStatus( OrderId orderId, const IBString &status, int filled,
	   int remaining, double avgFillPrice, int permId, int parentId,
	   double lastFillPrice, int clientId, const IBString& whyHeld)

{
	if( orderId == m_orderId) {
		if( m_state == ST_PLACEORDER_ACK && (status == "PreSubmitted" || status == "Submitted"))
			m_state = ST_CANCELORDER;

		if( m_state == ST_CANCELORDER_ACK && status == "Cancelled")
			m_state = ST_PING;

		LOGGER(DEBUG_FLAG,  "Order: id=" << orderId << ", status=" << status.c_str());
		disconnect();
	}
}

void PosixTestClient::nextValidId( OrderId orderId)
{
	m_orderId = orderId;

	m_state = ST_PLACEORDER;
}

void PosixTestClient::currentTime( long time)
{
	if ( m_state == ST_PING_ACK) {

		time_t now = ::time(NULL);
		m_sleepDeadline = now + SLEEP_BETWEEN_PINGS;

		m_state = ST_IDLE;
	}
}

void PosixTestClient::error(const int id, const int errorCode, const IBString errorString)
{
	LOGGER(ERROR_FLAG, "Error id=" << id << ",errorCode=" << errorCode << ", msg=" << errorString.c_str());
	if( id == -1 && errorCode == 1100) // if "Connectivity between IB and TWS has been lost"
		disconnect();
}

void PosixTestClient::tickPrice( TickerId tickerId, TickType field, double price, int canAutoExecute) {}
void PosixTestClient::tickSize( TickerId tickerId, TickType field, int size) {}
void PosixTestClient::tickOptionComputation( TickerId tickerId, TickType tickType, double impliedVol, double delta,
											 double optPrice, double pvDividend,
											 double gamma, double vega, double theta, double undPrice) {}
void PosixTestClient::tickGeneric(TickerId tickerId, TickType tickType, double value) {}
void PosixTestClient::tickString(TickerId tickerId, TickType tickType, const IBString& value) {}
void PosixTestClient::tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const IBString& formattedBasisPoints,
							   double totalDividends, int holdDays, const IBString& futureExpiry, double dividendImpact, double dividendsToExpiry) {}
void PosixTestClient::openOrder( OrderId orderId, const Contract&, const Order&, const OrderState& ostate) {}
void PosixTestClient::openOrderEnd() {}
void PosixTestClient::winError( const IBString &str, int lastError) {}
void PosixTestClient::connectionClosed() {}
void PosixTestClient::updateAccountValue(const IBString& key, const IBString& val,
										  const IBString& currency, const IBString& accountName) {}
void PosixTestClient::updatePortfolio(const Contract& contract, int position,
		double marketPrice, double marketValue, double averageCost,
		double unrealizedPNL, double realizedPNL, const IBString& accountName){}
void PosixTestClient::updateAccountTime(const IBString& timeStamp) {}
void PosixTestClient::accountDownloadEnd(const IBString& accountName) {}
void PosixTestClient::contractDetails( int reqId, const ContractDetails& contractDetails) {}
void PosixTestClient::bondContractDetails( int reqId, const ContractDetails& contractDetails) {}
void PosixTestClient::contractDetailsEnd( int reqId) {}
void PosixTestClient::execDetails( int reqId, const Contract& contract, const Execution& execution) {}
void PosixTestClient::execDetailsEnd( int reqId) {}

void PosixTestClient::updateMktDepth(TickerId id, int position, int operation, int side,
									  double price, int size) {}
void PosixTestClient::updateMktDepthL2(TickerId id, int position, IBString marketMaker, int operation,
										int side, double price, int size) {}
void PosixTestClient::updateNewsBulletin(int msgId, int msgType, const IBString& newsMessage, const IBString& originExch) {}
void PosixTestClient::managedAccounts( const IBString& accountsList) {}
void PosixTestClient::receiveFA(faDataType pFaDataType, const IBString& cxml) {}
void PosixTestClient::historicalData(TickerId reqId, const IBString& date, double open, double high,
									  double low, double close, int volume, int barCount, double WAP, int hasGaps) {}
void PosixTestClient::scannerParameters(const IBString &xml) {}
void PosixTestClient::scannerData(int reqId, int rank, const ContractDetails &contractDetails,
	   const IBString &distance, const IBString &benchmark, const IBString &projection,
	   const IBString &legsStr) {}
void PosixTestClient::scannerDataEnd(int reqId) {}
void PosixTestClient::realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
								   long volume, double wap, int count) {}
void PosixTestClient::fundamentalData(TickerId reqId, const IBString& data) {}
void PosixTestClient::deltaNeutralValidation(int reqId, const UnderComp& underComp) {}
void PosixTestClient::tickSnapshotEnd(int reqId) {}
void PosixTestClient::marketDataType(TickerId reqId, int marketDataType) {}
void PosixTestClient::commissionReport( const CommissionReport& commissionReport) {}

}
