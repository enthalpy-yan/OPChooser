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

#include "restclient.h"
#include "option.h"
#include "optionCollection.h"
#include "optionFactory.h"

/**
 *  Utility functions wrapper for my application.
 */
class MyAppHelper {

private:
    static const std::string GOOGLE_API_PREFIXURL;
    static const std::string YAHOO_YQL_API_PREFIXURL;
    static std::string YAHOO_YQL_QUERY;
    static const std::string YAHOO_YQL_API_SUFFIX;
    static bool instanceFlag;
    static MyAppHelper *single;
    MyAppHelper() {} //private constructor for Singleton Pattern.
public:
    static MyAppHelper& getInstance();
    ~MyAppHelper() { 
        instanceFlag = false; 
    }
    std::string httpGetRequest(const std::string& url); 
    std::string getOptions(std::string stockSymbol, std::string expDate);
    OptionCollection getOptionList(std::string& jsonString);
    double getStockPrice(const std::string& stockName);
    double s_to_d(const std::string& strPrice);
};

#endif
