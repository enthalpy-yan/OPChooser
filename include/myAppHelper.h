#ifndef _STOCK_PRICE_HELPER_H_
#define _STOCK_PRICE_HELPER_H_

#include <iostream>
#include <cstdio>
#include <string>

#include "../include/restclient.h"
#include "json/json.h"

/**
 *  Utility functions wrapper for my application.
 */
class MyAppHelper {

private:
    static const std::string PREFIXURL;
    static bool instanceFlag;
    static MyAppHelper *single;
    MyAppHelper() {} //private constructor for Singleton Pattern.
public:
    static MyAppHelper& getInstance();
    ~MyAppHelper() { 
      instanceFlag = false; 
    }
    double getStockPrice(const std::string& stockName);
    double s_to_d(const std::string& strPrice);

};

#endif
