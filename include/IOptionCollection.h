/**
 * iterator pattern
 */
#ifndef _I_OPTION_COLLECTION_H_
#define _I_OPTION_COLLECTION_H_

#include "Option.h"
#include "IOptionIterator.h"

/**
 *  Interface for option collection.
 */
class IOptionCollection {

public:
  virtual IOptionIterator* getIterator() = 0;
  virtual Option& operator[](int itemIndex) = 0;
  virtual int count() = 0;
};

#endif
