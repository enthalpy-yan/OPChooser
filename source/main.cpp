#include <iostream>
#include <cstdio>
#include <string>
#include <json/json.h>
#include <boost/date_time/gregorian/gregorian.hpp>

#include "restclient.h"
#include "myAppHelper.h"

int main() {
    
    MyAppHelper &appHelper = MyAppHelper::getInstance();
    // double p1 = appHelper.getStockPrice("GOOG");
    // cout << "Current Price for GOOG is: " << p1 << endl;
    // double p2 = appHelper.getStockPrice("MSFT");
    // cout << "Current Price for MSFT is: " << p2 << endl;
    // cout << appHelper.getOptions("MSFT", "2013-12") << endl;
    OptionCollection optionList = appHelper.getOptionListByOptionType("GOOG", "2013-12", PUT);
    
    IOptionIterator *iter = optionList.getIterator();

    for ( Option s = iter->firstOption(); iter->isDone() == false; s = iter->nextOption() ) {
        std::cout << s << std::endl;
    }

    return 0;
}
