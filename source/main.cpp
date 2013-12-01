#include <iostream>
#include <cstdio>
#include <string>

#include "myAppHelper.h"
#include "logger.h"

int main() {
  LOGGER_CONF("", Logger::screen_on, DEBUG_FLAG, DEBUG_FLAG);

  double p1 = GET_STOCK_PRICE("GOOG");
  // cout << "Current Price for GOOG is: " << p1 << endl;
  OptionCollection optionList = GET_OPTIONS("GOOG", "2013-12", PUT);

  IOptionIterator *iter = optionList.getIterator();

  for ( Option p = iter->firstOption(); iter->isDone() == false; p = iter->nextOption() ) {
  }

  return 0;
}
