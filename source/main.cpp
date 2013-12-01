#include <iostream>
#include <cstdio>
#include <string>
#include <boost/program_options.hpp>

#include "myAppHelper.h"
#include "logger.h"

int main(int ac, char* av[]) {
  LOGGER_CONF("", Logger::screen_on, ERROR_FLAG, ERROR_FLAG);

  try {

    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
      ("help,h", "Print help messages")
      ("verbose,v", "Print words with verbosity")
    ;

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(ac, av, desc), vm);
    boost::program_options::notify(vm);

    if (vm.count("help")) {
      cout << desc << "\n";
      return 0;
    }

    if (vm.count("verbose")) {
      LOGGER_CONF("", Logger::screen_on, DEBUG_FLAG, DEBUG_FLAG);
      LOGGER(DEBUG_FLAG, "Turn on verbose mode...");
    } 

    // double p1 = GET_STOCK_PRICE("GOOG");
    // cout << "Current Price for GOOG is: " << p1 << endl;

    OptionCollection optionList = GET_OPTIONS("GOOG", "2013-12-21", CALL);

    // IOptionIterator *iter = optionList.getIterator();

    // for ( Option p = iter->firstOption(); iter->isDone() == false; p = iter->nextOption() ) {
    //   std:cout << p << std::endl;
    // }

  } catch(exception& e) {
    LOGGER(ERROR_FLAG, "error: " << e.what());
    return 1;
  } catch(...) {
    LOGGER(ERROR_FLAG, "Exception of unknown type!");
  }

  return 0;
}
