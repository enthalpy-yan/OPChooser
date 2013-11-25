#include "../include/optionFactory.h"

Option& OptionFactory::createOption(string stockName, string optionSymbol, double strikePrice, 
    double purchasePrice, double optionPrice, OptionType optionType, string purchaseDate, string expirationDate) {
    Option *p = new Option(stockName);
    p->setOptionSymbol(optionSymbol);
    p->setStrikePrice(strikePrice);
    p->setPurchasePrice(purchasePrice);
    p->setOptionPrice(optionPrice);
    p->setOptionType(optionType);
    p->setPurchaseDate(expirationDate);
    p->setExpirationDate(expirationDate);
    return *p;
}