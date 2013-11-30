#include <iostream>
#include <cstdio>
#include <string>

#include "myAppHelper.h"
#include "logger.h"

int main() {

  double p1 = GET_STOCK_PRICE("GOOG");
  cout << "Current Price for GOOG is: " << p1 << endl;
  OptionCollection optionList = GET_OPTIONS("GOOG", "2013-12", CALL);

  IOptionIterator *iter = optionList.getIterator();

  for ( Option s = iter->firstOption(); iter->isDone() == false; s = iter->nextOption() ) {
      std::cout << s << std::endl;
  }

  DEBUG_CONF("", Logger::screen_on, DEBUG_FLAG, ERROR_FLAG);
  DEBUG(ERROR_FLAG, "12312312 " << "world");
  DEBUG(DEBUG_FLAG, "hello " << "world");

  return 0;
}
