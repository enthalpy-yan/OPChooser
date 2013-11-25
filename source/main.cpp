#include <iostream>
#include <cstdio>
#include <cstring>

#include "../include/restclient.h"
#include "../include/stockPriceHelper.h"
#include "json/json.h"

using namespace std;

int main() {
    double p1 = StockPriceHelper::getPrice("GOOG");
    cout << "Current Price for GOOG is: " << p1 << endl;
    double p2 = StockPriceHelper::getPrice("MSFT");
    cout << "Current Price for MSFT is: " << p2 << endl;
    return 0;
}
