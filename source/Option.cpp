#include "Option.h"

Option::Option() {}

Option::Option(string stockName) {

	this->stockName = stockName;
}

Option::~Option(){

}

ostream& operator<<(ostream& os, const Option& option) {
  os << "{ " << "stockName: " << option.stockName      << ", "
     << "optionSymbol: "      << option.optionSymbol   << ", "
     << "strikePrice: "       << option.strikePrice    << ", "
     << "purchasePrice: "     << option.purchasePrice  << ", "
     << "optionPrice: "       << option.optionPrice    << ", "
     << "optionType: "        << option.optionType     << ", "
     << "purchaseDate: "      << option.purchaseDate   << ", "
     << "expirationDate: "    << option.expirationDate << " }";
  return os;
}

void Option::setStockName(string stockName) {
	this->stockName = stockName;
}


string Option::getStockName() {
	return this->stockName;
}

void Option::setOptionSymbol(string optionSymbol) {
	this->optionSymbol = optionSymbol;
}

string Option::getOptionSymbol() {
	return this->optionSymbol;
}

void Option::setStrikePrice(double strikePrice) {
	this->strikePrice = strikePrice;
}

double Option::getStrikePrice() {
	return this->strikePrice;
}

void Option::setPurchasePrice(double purchasePrice) {
	this->purchasePrice = purchasePrice;
}

double Option::getPurchasePrice() {
	return this->purchasePrice;
}

void Option::setOptionPrice(double optionPrice) {
	this->optionPrice = optionPrice;
}

double Option::getOptionPrice() {
	return this->optionPrice;
}

void Option::setOptionType(OptionType type) {
	this->optionType = type;
}

OptionType Option::getOptionType() {
	return this->optionType;
}

void Option::setPurchaseDate(string purchaseDate) {
	try {
		boost::gregorian::date d(boost::gregorian::from_undelimited_string(purchaseDate));
		this->purchaseDate = d;
    } catch (std::exception& e) {
     	std::cout << "Exception: " <<  e.what() << std::endl;
    }
}

string Option::getPurchaseDate() {
	return boost::gregorian::to_simple_string(this->purchaseDate);
}

void Option::setExpirationDate(string expirationDate) {
	try {
		boost::gregorian::date d(boost::gregorian::from_undelimited_string(expirationDate));
		this->expirationDate = d;
    } catch (std::exception& e) {
     	std::cout << "Exception: " <<  e.what() << std::endl;
    }
}

string Option::getExpirationDate() {
	return boost::gregorian::to_simple_string(this->expirationDate);
}
