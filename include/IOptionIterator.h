/**
 * iterator pattern
 */
#ifndef _I_OPTION_ITERATOR_
#define _I_OPTION_ITERATOR_

#include "Option.h"

/**
 *  Interface for option iterator.
 */
class IOptionIterator {

public:
  virtual Option firstOption() = 0;
  virtual Option nextOption() = 0; 
  virtual Option currentOption() = 0;
  virtual bool isDone() = 0;    
};

#endif
