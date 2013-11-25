/**
 * iterator pattern
 */
#ifndef _OPTION_COLLECTION_H_
#define _OPTION_COLLECTION_H_

#include <iostream>
#include <vector>

#include "../include/iOptionCollection.h"
#include "../include/option.h"
#include "../include/OptionIterator.h"

/**
 * Concrete Collection Object for saving option data.
 */
class OptionCollection : public IOptionCollection {
    std::vector<Option> options_;

public:

    OptionCollection(void) {}
    void addOption(Option option); //add new option to option list.
    IOptionIterator* GetIterator(); //retrieve option iterator from current option list.
    Option& operator[](int itemIndex); //get option with the given index.
    int Count();
};

#endif