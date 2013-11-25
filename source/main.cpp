#include <iostream>
#include <cstdio>
#include <cstring>

#include "../include/restclient.h"
#include "../include/myAppHelper.h"
#include "../include/optionCollection.h"
#include "../include/option.h"
#include "../include/optionFactory.h"
#include "json/json.h"

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

    IOptionIterator *iter = optionList.GetIterator();

    for (Option s = iter->FirstOption(); iter->IsDone() == false; s = iter->NextOption() ) {
        std::cout << s.getStockName() << std::endl;
    }
}
