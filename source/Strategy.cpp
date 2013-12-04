#include <iostream>

#include "Strategy.h"

using namespace std; 

Strategy::Strategy() {}

Strategy::~Strategy() {}

void Strategy::AlgrithmInterface(vector<Option>, multimap<double, vector<Option> >&) {}

StrategyA::StrategyA() {} 

StrategyA::~StrategyA() {}

void StrategyA::AlgrithmInterface(vector<Option> vec, multimap<double, vector<Option> > &resultmap) {

  LOGGER(DEBUG_FLAG, "Applied Strategy A to Combinations: " 
                      << vec[0].getOptionSymbol() << " "
                      << vec[1].getOptionSymbol() << " "
                      << vec[2].getOptionSymbol() << " "
                      << vec[3].getOptionSymbol());

  double payOff;
  vector<Option> temp;

  double tempPrice = vec[0].getStrikePrice() + 20;

  if (tempPrice <= (vec[0]).getStrikePrice()) {
    payOff = -(vec[3]).getOptionPrice() - (vec[0]).getOptionPrice() + (vec[1]).getOptionPrice() + (vec[2]).getOptionPrice()
    + ((vec[0]).getStrikePrice() - tempPrice);
  } else if ((tempPrice > vec[0].getStrikePrice() && tempPrice < (vec[2]).getStrikePrice()) || tempPrice == (vec[2]).getStrikePrice()) {
    payOff = -(vec[3]).getOptionPrice() - (vec[0]).getOptionPrice() + (vec[1]).getOptionPrice() + (vec[2]).getOptionPrice()
    + ((vec[2]).getStrikePrice() - tempPrice) + (tempPrice - (vec[0]).getStrikePrice());
  } else {
    payOff = -(vec[3]).getOptionPrice() - (vec[0]).getOptionPrice() + (vec[1]).getOptionPrice()
    + (vec[2]).getOptionPrice() + ((tempPrice - (vec[2]).getStrikePrice()) - (tempPrice) - (vec[2]).getStrikePrice());
  }

  for ( unsigned int i = 0 ; i < vec.size(); i++ ) {
    temp.push_back(vec.at(i));
  }

  typedef pair<double, vector<Option> > Pair;
  resultmap.insert(Pair(payOff,temp));
}

StrategyB::StrategyB() {}

StrategyB::~StrategyB() {}

void StrategyB::AlgrithmInterface(vector<Option> vec, multimap<double, vector<Option> > &resultmap) {

  LOGGER(DEBUG_FLAG, "Applied Strategy B to Combinations: " 
                      << vec[0].getOptionSymbol() << " "
                      << vec[1].getOptionSymbol() << " "
                      << vec[2].getOptionSymbol() << " "
                      << vec[3].getOptionSymbol());

  double payOff;
  vector<Option> temp;
  double tempPrice = vec[0].getStrikePrice() + 20;

  if (tempPrice <= (vec[0]).getStrikePrice()) {
    payOff = (vec[3]).getOptionPrice() + (vec[0]).getOptionPrice() - (vec[1]).getOptionPrice()
    - (vec[2]).getOptionPrice() + ((vec[0]).getStrikePrice() - tempPrice)
    - ((vec[2]).getStrikePrice() - tempPrice);
  } else if (((vec[0]).getStrikePrice() < tempPrice) && (tempPrice <= (vec[2]).getStrikePrice())) {
    payOff = (vec[3]).getOptionPrice() + (vec[0]).getOptionPrice() - (vec[1]).getOptionPrice() - (vec[2]).getOptionPrice() - ((vec[2]).getStrikePrice() - tempPrice)
    - (tempPrice - (vec[0]).getStrikePrice());
  } else {
    payOff = (vec[3]).getOptionPrice() + (vec[0]).getOptionPrice() - (vec[0]).getOptionPrice()
    - (vec[2]).getOptionPrice() + (tempPrice - (vec[2]).getStrikePrice()) - (tempPrice - (vec[0]).getStrikePrice());
  }

  for (unsigned int i = 0; i < vec.size(); i++) {
    temp.push_back(vec.at(i));
  }

  typedef pair<double, vector<Option> > Pair;
  resultmap.insert(Pair(payOff,temp));
}
 
Context::Context(Strategy* strategy) {
  this->strategy = strategy;
}

Context::~Context() {
}
 
void Context::DoAction(vector<Option> vec, multimap<double, vector<Option> > &resultmap) {
  this->strategy->AlgrithmInterface(vec,resultmap);
}