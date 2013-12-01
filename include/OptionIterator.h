/**
 * iterator pattern
 */
#ifndef _OPTION_ITERATOR_H_
#define _OPTION_ITERATOR_H_

#include "IOptionIterator.h"
#include "IOptionCollection.h"
#include "OptionCollection.h"

/**
 * Concrete iterator for traversing option collection.
 */
class OptionIterator : public IOptionIterator {
  IOptionCollection *optionCollection;
  int currentIndex_;

public:
  OptionIterator(IOptionCollection *oc);

  Option firstOption();

  Option nextOption();

  Option currentOption();

  bool isDone();
};

#endif
