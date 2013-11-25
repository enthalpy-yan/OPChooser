#include "../include/optionCollection.h"

void OptionCollection::addOption(Option option) {
    options_.push_back(option);
}

IOptionIterator* OptionCollection::GetIterator() {
    IOptionIterator *iter = new OptionIterator(this); 
    return iter;
}

Option& OptionCollection::operator[](int itemIndex) {
    return options_[itemIndex];
} 

int OptionCollection::Count() {
    return options_.size();
}