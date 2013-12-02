#include <iostream>
#include <cstdio>
#include <string>
#include <boost/program_options.hpp>
#include <map>
namespace po = boost::program_options;

#include "MyAppHelper.h"
#include "Logger.h"
#include "OptionFilter.h"
#include "TemplateOne.h"

int main(int ac, char* av[]) {
  LOGGER_CONF("", Logger::screen_on, ERROR_FLAG, ERROR_FLAG);

  try {

    po::options_description desc("Allowed options");
    desc.add_options()
      ("help,h", "Print help messages")
      ("verbose,v", "Print words with verbosity")
      ("output,o", po::value<std::string>(), "Set logging output file.")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
      cout << desc << "\n";
      return 0;
    }

    if (vm.count("verbose") && vm.count("output")) {
      LOGGER_CONF(vm["output"].as<std::string>(), Logger::screen_on | Logger::file_on, DEBUG_FLAG, DEBUG_FLAG);
    } else if (vm.count("verbose")) {
      LOGGER_CONF("", Logger::screen_on, DEBUG_FLAG, DEBUG_FLAG);
    } else if (vm.count("output")) {
      LOGGER_CONF(vm["output"].as<std::string>(), Logger::file_on, DEBUG_FLAG, DEBUG_FLAG);
    } 

    OptionCollection optionListCall = GET_OPTIONS("AAPL", "2013-12", CALL);
    OptionCollection optionListPut = GET_OPTIONS("AAPL", "2013-12", PUT);

    OptionFilter *of = new TemplateOne(optionListCall, optionListPut);
    vector<Option> resultVector = of->filter();

    multimap<double,vector<string> > resultMap;

    ORDER(resultVector, resultMap);
  
    double max;
    map<double,vector<string> >::iterator it;

    for (it = resultMap.begin(); it != resultMap.end(); it++) {  
      if(it == resultMap.begin())
         max = it->first;
      else {
        if(it->first > max)
           max = it->first;
        else
          continue;
      }
    }

    cout << "You should select this combination" << endl;

    it = resultMap.find(max);
    cout << it->second.size() << endl;
    for (unsigned int i = 0; i < it->second.size(); i++)
      cout << it->second.at(i) << endl;

    cout << "And the payOff is " << max << endl;

  } catch(exception& e) {
    LOGGER(ERROR_FLAG, e.what());
    exit(1);
  } catch(...) {
    LOGGER(ERROR_FLAG, "Exception of unknown type!");
  }

  return 0;
}
