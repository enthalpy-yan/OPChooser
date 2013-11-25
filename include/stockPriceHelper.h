#ifndef _STOCK_PRICE_HELPER_H_
#define _STOCK_PRICE_HELPER_H_

#include <iostream>
#include <cstdio>
#include <string>

#include "../include/restclient.h"
#include "json/json.h"

class StockPriceHelper {
private:
    static const std::string PREFIXURL;
public:
    static double getPrice(const std::string& stockName);
    static double s_to_d(const std::string& strPrice);
};

#endif
