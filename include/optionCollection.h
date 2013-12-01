/**
 * iterator pattern
 */
#ifndef _OPTION_COLLECTION_H_
#define _OPTION_COLLECTION_H_

#include <iostream>
#include <vector>

#include "IOptionCollection.h"
#include "Option.h"
#include "OptionIterator.h"

/**
 * Concrete Collection Object for saving option data.
 */
class OptionCollection : public IOptionCollection {
  std::vector<Option> options_;

public:

  OptionCollection(void) {}
  void addOption(Option option); //add new option to option list.
  IOptionIterator* getIterator(); //retrieve option iterator from current option list.
  Option& operator[](int itemIndex); //get option with the given index.
  int count();
};

#endif
