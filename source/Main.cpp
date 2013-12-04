#include <iostream>
#include <cstdio>
#include <string>
#include <boost/program_options.hpp>
#include <map>
#ifdef _WIN32
# include <windows.h>
# define sleep( seconds) Sleep( seconds * 1000);
#else
# include <unistd.h>
#endif

namespace po = boost::program_options;

#include "PosixTestClient.h"
#include "MyAppHelper.h"
#include "Logger.h"
#include "OptionFilter.h"
#include "TemplateOne.h"

const unsigned MAX_ATTEMPTS = 1;
const unsigned SLEEP_TIME = 10;

int main(int ac, char* av[]) {
  LOGGER_CONF("", Logger::screen_on, ERROR_FLAG, ERROR_FLAG);

  try {

    po::options_description desc("Allowed options");
    desc.add_options()
      ("help,h", "Print help messages.")
      ("verbose,v", "Print words with verbosity.")
      ("output,o", po::value<std::string>(), "Set logging output file.")
      ("ticker,t", po::value<std::string>()->required(), "Set the name of ticker.")
      ("date,d", po::value<std::string>()->required(), "Set expiration date for the given ticker.")
      ("order", "Place an order in IB with the results. (Demo)");
      
    po::variables_map vm;
    po::store(
      po::command_line_parser(ac,av)
      .options(desc)
      .style(
          po::command_line_style::unix_style
        | po::command_line_style::allow_long_disguise)
      .run(),
    vm);

    if (vm.count("help")) {
      cout << desc << "\n";
      return 0;
    }

    po::notify(vm);

    if (vm.count("verbose") && vm.count("output")) {
      LOGGER_CONF(vm["output"].as<std::string>(), Logger::screen_on | Logger::file_on, DEBUG_FLAG, DEBUG_FLAG);
    } else if (vm.count("verbose")) {
      LOGGER_CONF("", Logger::screen_on, DEBUG_FLAG, DEBUG_FLAG);
    } else if (vm.count("output")) {
      LOGGER_CONF(vm["output"].as<std::string>(), Logger::file_on, DEBUG_FLAG, DEBUG_FLAG);
    }  

    OptionCollection optionListCall = GET_OPTIONS(vm["ticker"].as<std::string>(), vm["date"].as<std::string>(), CALL);
    OptionCollection optionListPut = GET_OPTIONS(vm["ticker"].as<std::string>(), vm["date"].as<std::string>(), PUT);

    OptionFilter *of = new TemplateOne(optionListCall, optionListPut);
    vector<Option> resultVector = of->filter();

    multimap<double,vector<Option> > resultMap;

    ORDER(resultVector, resultMap);
  
    LOGGER(DEBUG_FLAG, "the size of portfolio is: " << resultMap.size());
    
    double max;
    map<double,vector<Option> >::iterator it;

    for (it = resultMap.begin(); it != resultMap.end(); it++) {  
      if(it == resultMap.begin()) {
         max = it->first;
         cout << max << endl;
      } else if (it->first > max) {
           max = it->first;
           cout << max << endl;
      } else
          continue;
    }

    cout << "============================================" << endl;
    cout << "  The optimum portfolio has been selected" << endl;
    it = resultMap.find(max);
    cout << endl;

    for(unsigned int i = 0; i < it->second.size(); i++)
      cout << "            " << it->second.at(i) << endl;

    cout << endl;
    cout << "  PayOff: " << max << endl;
    cout << "============================================" << endl;

    if (!vm.count("order")) {
      return 0;
    }

    int clientId = 0;
    unsigned attempt = 0;

    printf( "Start of POSIX Socket Client Test %u\n", attempt);

    for (;;) {
      ++attempt;
      printf( "Attempt %u of %u\n", attempt, MAX_ATTEMPTS);

      IB::PosixTestClient client;

      client.connect( "127.0.0.1", 7496, clientId);

      while (client.isConnected()) {
        vector<Option> resultVector = it->second;
        client.processMessages(resultVector);
      }

      if( attempt >= MAX_ATTEMPTS) {
        break;
      }

      printf( "Sleeping %u seconds before next attempt\n", SLEEP_TIME);
      sleep( SLEEP_TIME);
    }

    printf ( "End of POSIX Socket Client Test\n");

    return 0;

  } catch (std::length_error) { 
    LOGGER(ERROR_FLAG, "!!!Invalid ticker name.");
  } catch(exception& e) {
    LOGGER(ERROR_FLAG, e.what());
    exit(1);
  } catch(...) {
    LOGGER(ERROR_FLAG, "Exception of unknown type!");
  }

}
