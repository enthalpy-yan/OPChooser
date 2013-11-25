/**
 * iterator pattern
 */
#ifndef _I_OPTION_ITERATOR_
#define _I_OPTION_ITERATOR_

#include "../include/option.h"

/**
 *  Interface for option iterator.
 */
class IOptionIterator {

public:
    virtual Option FirstOption() = 0;
    virtual Option NextOption() = 0;
    virtual Option CurrentOption() = 0;
    virtual bool IsDone() = 0;    
};

#endif