#include "MyAppHelper.h"

const std::string MyAppHelper::GOOGLE_API_PREFIXURL 
      = "http://finance.google.com/finance/info?client=ig&q=";
const std::string MyAppHelper::YAHOO_YQL_API_PREFIXURL           
      = "http://query.yahooapis.com/v1/public/yql?q=";
std::string MyAppHelper::YAHOO_YQL_QUERY 
      = "select [query] from yahoo.finance.options where symbol=\"[o_name]\" and expiration=\"[o_exp_date]\"";
const std::string MyAppHelper::YAHOO_YQL_API_SUFFIX 
      = "store://datatables.org/alltableswithkeys";

bool MyAppHelper::instanceFlag = false;

MyAppHelper* MyAppHelper::single = NULL;

MyAppHelper& MyAppHelper::getInstance() {
  if(!instanceFlag) {
    single = new MyAppHelper();
    instanceFlag = true;
    return *single;
  } else {
    return *single;
  }
}

void MyAppHelper::StrategySet(vector<Option> v,multimap<double,vector<string> > &resultmap) {
  double LVal;
  double RVal;
  Context* pcon;
  Strategy* pStr;

  boost::gregorian::date purchaseDate = boost::gregorian::from_simple_string(v.at(2).getPurchaseDate());
  boost::gregorian::date expirationDate = boost::gregorian::from_simple_string(v.at(0).getExpirationDate());
  boost::gregorian::date_period dp( purchaseDate, expirationDate );

  LVal = ((v.at(2).getStrikePrice() - v.at(0).getStrikePrice()) * exp((-0.08) * dp.length().days()));
  RVal = (v.at(3)).getOptionPrice() - (v.at(1)).getOptionPrice() - (v.at(1)).getOptionPrice()+ (v.at(0)).getOptionPrice();

  if (LVal > RVal) {
    //Strategy 1
    pStr = new StrategyA();
    pcon = new Context(pStr);
    pcon->DoAction(v, resultmap);
  } else {
    //Strategy 2
    pStr = new StrategyB();
    pcon = new Context(pStr);
    pcon->DoAction(v,resultmap);
  }
}

void MyAppHelper::Order(vector<Option> v,multimap<double,vector<string> > &resultmap) {
  int lenght= v.size();
  vector<Option> newvector;
  vector<Option> finalresult;
  
  for(int i = 0; i < lenght - 2; i += 2) {
    if (!newvector.empty())
      newvector.clear();

    newvector.push_back(v.at(i));
    newvector.push_back(v.at(i + 1));

    for(int m = i + 2; m < lenght; m += 2) {
      newvector.push_back(v.at(m));
      newvector.push_back(v.at(m + 1));
      StrategySet(newvector, resultmap);
      newvector.pop_back();
      newvector.pop_back();   
    }
  }
}

/**
 * Convert string to double
 */
double MyAppHelper::s_to_d(const std::string& strPrice) {
  return std::atof(strPrice.c_str());
}

/**
 * Retrieve date info from stock symbol. e.g. MSFT131227P00038000 -> 20131227
 * @param  stockSymbol 
 * @return date
 */
std::string MyAppHelper::getDateFromSymbol(std::string optionSymbol, std::string type) {
  int index = optionSymbol.find_last_of(type);
  std::string rawDateStr = optionSymbol.substr(index - 6, 6);
  rawDateStr.insert(0, "20");
  return rawDateStr;
}

/**
 * Send http request to the target url and get the response.
 * @param  url 
 * @return response strings
 */
std::string MyAppHelper::httpGetRequest(const std::string& url) {
  RestClient::response r = RestClient::get(url);
  return r.body;
}

/**
 * Retrieve real time stock price.
 * @param  stockName name of the stock
 * @return stock price
 */
double MyAppHelper::getStockPrice(const std::string& stockName) {
  std::string targetUrl = GOOGLE_API_PREFIXURL;
  targetUrl.append(stockName);
  std::string responseJson = httpGetRequest(targetUrl);

  //trim stock data in order to fit in json object.
  responseJson.erase(responseJson.begin(), responseJson.begin() + 5);
  responseJson.erase(responseJson.end() - 2, responseJson.end());

  Json::Value root; //will contains the root value(json object) after parsing.
  Json::Reader reader;
  bool parsedSuccess = reader.parse(responseJson, root, false);

  if (not parsedSuccess) {
    // report to the user the failure and their locations in the document.
    LOGGER(ERROR_FLAG, "Failed to parse Stock JSON" << std::endl << reader.getFormatedErrorMessages());
    exit(1);
  }

  // Print response in styled json.
  // std::cout << root.toStyledString() << std::endl;

  //Get the value of the member of root named 'l_fix'(stock price).
  const Json::Value stockPrice = root["l_fix"];

  if (not stockPrice.isNull()) {
    return MyAppHelper::s_to_d(stockPrice.asString());
  } else {
    exit(1);
  }
}

std::string MyAppHelper::buildYQLQuery(string query, string where1, string where2) {
  LOGGER(DEBUG_FLAG, "Building Yahoo YQL query...");
  string yqlQuery(MyAppHelper::YAHOO_YQL_QUERY);

  yqlQuery.replace(yqlQuery.find("[query]"), 7, "option");
  yqlQuery.replace(yqlQuery.find("[o_name]"), 8, where1);
  yqlQuery.replace(yqlQuery.find("[o_exp_date]"), 12, where2);

  LOGGER(DEBUG_FLAG, "YQL Query *** " << yqlQuery << " ***");

  string request(MyAppHelper::YAHOO_YQL_API_PREFIXURL);
  request.append(curl_escape(yqlQuery.c_str(), yqlQuery.size()));
  request.append("&format=json&env=");
  request.append(curl_escape(MyAppHelper::YAHOO_YQL_API_SUFFIX.c_str(),
                 MyAppHelper::YAHOO_YQL_API_SUFFIX.size()));
  LOGGER(DEBUG_FLAG, "Waiting for response from server...");
  return request;
}

/**
 * Retrieve all options with the given stock symbol and expiration date.
 * expDate... 2013-11 or 2013-12 Because the API limitation, we cannot query historical option data.
 */
std::string MyAppHelper::getOptions(string stockSymbol, string expDate) {
  MyAppHelper &appHelper = MyAppHelper::getInstance();
  string request = buildYQLQuery("option", stockSymbol, expDate);
  return appHelper.httpGetRequest(request);
}

/**
 * Retrieve all options from json string by option type and save them into a option collection.
 * @param  jsonString response string from yahoo yql web service. 
 * @return 
 */
OptionCollection MyAppHelper::getOptionListByOptionType(std::string stockName, std::string expDate, OptionType otype) {
  LOGGER(DEBUG_FLAG, "Started to retrieving Option data from YQL web service.. " << "Symbol: " << stockName << " Type: " << (otype ? "PUT" : "CALL"));
  OptionCollection optionList;
  OptionFactory *optionFactory = new OptionFactory();
  Json::Value root; //will contains the root value(json object) after parsing.
  Json::Reader reader;

  std::string jsonString = getOptions(stockName, expDate);

  double currentStockPrice = getStockPrice(stockName);
  boost::gregorian::date cDate(boost::gregorian::day_clock::local_day());
  std::string currentDate = boost::gregorian::to_iso_string(cDate);

  bool parsedSuccess = reader.parse(jsonString, root, false);

  if (not parsedSuccess) {
    // report to the user the failure and their locations in the document.
    LOGGER(ERROR_FLAG, "Failed to parse Option JSON" << std::endl << reader.getFormatedErrorMessages());
    exit(1);
  }

  LOGGER(DEBUG_FLAG, "Retrieved Option data...");

  const Json::Value coutJsonValue = root["query"];

  if (coutJsonValue["count"] == 0) {
    LOGGER(ERROR_FLAG, "!!!Response from server is empty. Please check the ticker name or expiration date and also your network connection.");
    exit(1);
  }

  const Json::Value optionsChain = root["query"]["results"]["optionsChain"];
  LOGGER(DEBUG_FLAG, "Starting parsing Option data...");
  if (not optionsChain.isNull()) {
    for (unsigned int index = 0; index < optionsChain.size(); index++) {
      const Json::Value optionSymbol = optionsChain[index]["option"]["symbol"];
      const Json::Value optionType = optionsChain[index]["option"]["type"];
      if (otype == PUT) {
        if (optionType.asString() == "P") {
          const Json::Value optionSymbol = optionsChain[index]["option"]["symbol"];
          std::string oSymbol = optionSymbol.asString();
          const Json::Value optionStrikePrice = optionsChain[index]["option"]["strikePrice"];
          double oStrikePrice = s_to_d(optionStrikePrice.asString());
          const Json::Value optionPrice = optionsChain[index]["option"]["ask"];
          double oPrice = s_to_d(optionPrice.asString());
          std::string oExpirationDate= getDateFromSymbol(oSymbol, "P");
          Option &p = optionFactory->createOption(stockName, oSymbol, oStrikePrice, 
                                                  currentStockPrice, oPrice, PUT, currentDate, 
                                                  oExpirationDate);
          // LOGGER(DEBUG_FLAG, "Added new Option..." << p);
          optionList.addOption(p);
        }
      } else if (otype == CALL) {
        if (optionType.asString() == "C") {
          const Json::Value optionSymbol = optionsChain[index]["option"]["symbol"];
          std::string oSymbol = optionSymbol.asString();
          const Json::Value optionStrikePrice = optionsChain[index]["option"]["strikePrice"];
          double oStrikePrice = s_to_d(optionStrikePrice.asString());
          const Json::Value optionPrice = optionsChain[index]["option"]["ask"];
          double oPrice = s_to_d(optionPrice.asString());
          std::string oExpirationDate= getDateFromSymbol(oSymbol, "C");
          Option &p = optionFactory->createOption(stockName, oSymbol, oStrikePrice, 
                                                  currentStockPrice, oPrice, CALL, currentDate, 
                                                  oExpirationDate);
          // LOGGER(DEBUG_FLAG, "Added new Option..." << p);
          optionList.addOption(p);
        }
      }
    }
    LOGGER(DEBUG_FLAG, "Finished parse Option data... ");
    return optionList;
  } else {
      exit(1);
  }
}






