/**
 * factory pattern
 */
#ifndef _OPTION_FACTORY_H_
#define _OPTION_FACTORY_H_

#include "Option.h"

class OptionFactory {
public:
  OptionFactory();
  Option& createOption(string stockName);
  Option& createOption(string stockName, 
                       string optionSymbol, 
                       double strikePrice, 
                       double purchasePrice, 
                       double optionPrice,
                       OptionType optionType,
                       string purchaseDate,
                       string expirationDate);
};

#endif
