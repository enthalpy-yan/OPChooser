/**
 * iterator pattern
 */
#ifndef _OPTION_ITERATOR_H_
#define _OPTION_ITERATOR_H_

#include "../include/iOptionIterator.h"
#include "../include/iOptionCollection.h"
#include "../include/optionCollection.h"

/**
 * Concrete iterator for traversing option collection.
 */
class OptionIterator : public IOptionIterator {
    IOptionCollection *optionCollection;
    int currentIndex_;

public:
    OptionIterator(IOptionCollection *oc);
  
    Option FirstOption();
  
    Option NextOption();

    Option CurrentOption();

    bool IsDone();
};

#endif