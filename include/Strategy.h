#ifndef _STRATEGY_H_
#define _STRATEGY_H_
#include <vector>
#include <map>
#include <string>

#include "Option.h"

using namespace std;

class Strategy {

public:
  ~Strategy();
  virtual void AlgrithmInterface(vector<Option>, multimap<double, vector<string> >&);
  // map<double,vector<string>> resultmap;
  Strategy();

};

class StrategyA : public Strategy {

public:
  StrategyA();
  ~StrategyA();
  void AlgrithmInterface(vector<Option>, multimap<double, vector<string> >&);

};

class StrategyB : public Strategy {

public:
  StrategyB();
  ~StrategyB();
  void AlgrithmInterface(vector<Option>,multimap<double, vector<string> >&);

};



class Context {

public:
  Context(Strategy*);
  ~Context();
  void DoAction(vector<Option>, multimap<double,vector<string> >&);
private:
  Strategy* strategy;

};

#endif