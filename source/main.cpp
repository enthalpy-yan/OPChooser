#include <iostream>
#include <cstdio>
#include <cstring>
#include <json/json.h>

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

    Option &p1 = optionFactory->createOption("111111");
    Option &p2 = optionFactory->createOption("222222");

    OptionCollection optionList;

    optionList.addOption(Option(p1));
    optionList.addOption(Option(p2));

    IOptionIterator *iter = optionList.getIterator();

    for (Option s = iter->firstOption(); iter->isDone() == false; s = iter->nextOption() ) {
        std::cout << s << std::endl;
    }
}
