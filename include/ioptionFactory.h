#ifndef _I_OPTION_FACTORY_H_
#define _I_OPTION_FACTORY_H_

#include "../include/option.h"

class IOptionFactory {
public:
    virtual Option& createOption(string stockName, 
                                string optionSymbol, 
                                double strikePrice, 
                                double purchasePrice, 
                                double optionPrice,
                                OptionType optionType,
                                string purchaseDate,
                                string expirationDate) = 0;
};

#endif