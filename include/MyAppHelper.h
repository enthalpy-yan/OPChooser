/**
 * singleton pattern
 */
#ifndef _STOCK_PRICE_HELPER_H_
#define _STOCK_PRICE_HELPER_H_

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <json/json.h>

#include "Restclient.h"
#include "Option.h"
#include "OptionCollection.h"
#include "OptionFactory.h"
#include "Logger.h"

#define GET_STOCK_PRICE(stockName) MyAppHelper::getInstance().getStockPrice(stockName);
#define GET_OPTIONS(stockSymbol, \
                    expDate, \
                    otype) \
                    MyAppHelper::getInstance().getOptionListByOptionType(\
                      stockSymbol, \
                      expDate, \
                      otype); 
#define SEND_HTTP_REQUEST(url) MyAppHelper::getInstance().httpGetRequest(url);

/**
 *  Utility functions wrapper for my application.
 */
class MyAppHelper {

private:
  MyAppHelper() {} //private constructor for Singleton Pattern.
  static const std::string GOOGLE_API_PREFIXURL;
  static const std::string YAHOO_YQL_API_PREFIXURL;
  static std::string YAHOO_YQL_QUERY;
  static const std::string YAHOO_YQL_API_SUFFIX;
  static bool instanceFlag;
  static MyAppHelper *single;
  std::string buildYQLQuery(string query, string where1, string where2);
  std::string getOptions(std::string stockSymbol, std::string expDate);
  std::string getDateFromSymbol(std::string optionSymbol, std::string type);
public:
  static MyAppHelper& getInstance();
  ~MyAppHelper() { 
      instanceFlag = false; 
  }
  std::string httpGetRequest(const std::string& url); 
  OptionCollection getOptionListByOptionType(std::string stockSymbol, std::string expDate, OptionType otype);
  double getStockPrice(const std::string& stockName);
  double s_to_d(const std::string& strPrice);
};

#endif
