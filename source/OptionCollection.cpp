#include "OptionCollection.h"

void OptionCollection::addOption(Option option) {
  options_.push_back(option);
}

IOptionIterator* OptionCollection::getIterator() {
  IOptionIterator *iter = new OptionIterator(this); 
  return iter;
}

Option& OptionCollection::operator[](int itemIndex) {
  return options_[itemIndex];
} 

int OptionCollection::count() {
  return options_.size();
}
