#ifndef _OPTION_FACTORY_H_
#define _OPTION_FACTORY_H_

#include "../include/ioptionFactory.h"

class OptionFactory: IOptionFactory {
public:
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