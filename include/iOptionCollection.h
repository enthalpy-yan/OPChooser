/**
 * iterator pattern
 */
#ifndef _I_OPTION_COLLECTION_H_
#define _I_OPTION_COLLECTION_H_

#include "../include/option.h"
#include "../include/iOptionIterator.h"

/**
 *  Interface for option collection.
 */
class IOptionCollection {

public:
    virtual IOptionIterator* GetIterator() = 0;
    virtual Option& operator[](int itemIndex) = 0;
    virtual int Count() = 0;
};

#endif