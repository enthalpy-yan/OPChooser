#include <iostream>
#include <cstdio>
#include <string>
#include <json/json.h>
#include <boost/date_time/gregorian/gregorian.hpp>

#include "restclient.h"
#include "myAppHelper.h"

using namespace std;

int main() {
    MyAppHelper &appHelper = MyAppHelper::getInstance();
    // double p1 = appHelper.getStockPrice("GOOG");
    // cout << "Current Price for GOOG is: " << p1 << endl;
    // double p2 = appHelper.getStockPrice("MSFT");
    // cout << "Current Price for MSFT is: " << p2 << endl;
    // cout << appHelper.getOptions("MSFT", "2013-12") << endl;

    OptionFactory *optionFactory = new OptionFactory();

    Option &p1 = optionFactory->createOption("111111", "11", 1,1,1, PUT, "20131010", "20131010");
    Option &p2 = optionFactory->createOption("222222");

    OptionCollection optionList;

    optionList.addOption(p1);
    optionList.addOption(p2);

    IOptionIterator *iter = optionList.getIterator();

    for ( Option s = iter->firstOption(); iter->isDone() == false; s = iter->nextOption() ) {
        std::cout << s << std::endl;
    }

    std::string s("20131009");
    boost::gregorian::date d(boost::gregorian::from_undelimited_string(s));
    std::cout << boost::gregorian::to_iso_extended_string(d) << std::endl;

    return 0;
}
