#include <iostream>
#include <cstdio>
#include <cstring>

#include "../include/restclient.h"
#include "../include/myAppHelper.h"
#include "json/json.h"

using namespace std;

int main() {
    MyAppHelper &appHelper = MyAppHelper::getInstance();
    double p1 = appHelper.getStockPrice("GOOG");
    cout << "Current Price for GOOG is: " << p1 << endl;
    double p2 = appHelper.getStockPrice("MSFT");
    cout << "Current Price for MSFT is: " << p2 << endl;
}
