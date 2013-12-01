#include "OptionFactory.h"

OptionFactory::OptionFactory() {}

Option& OptionFactory::createOption(string stockName) {
  Option *p = new Option(stockName);
  return *p;
}

Option& OptionFactory::createOption(string stockName, string optionSymbol, double strikePrice, 
  double purchasePrice, double optionPrice, OptionType optionType, string purchaseDate, string expirationDate) {
  Option *p = new Option(stockName);
  p->setOptionSymbol(optionSymbol);
  p->setStrikePrice(strikePrice);
  p->setPurchasePrice(purchasePrice);
  p->setOptionPrice(optionPrice);
  p->setOptionType(optionType);
  p->setPurchaseDate(purchaseDate);
  p->setExpirationDate(expirationDate);
  return *p;
}
