#include "OptionIterator.h"

OptionIterator::OptionIterator(IOptionCollection *oc) {
  this->optionCollection = oc;
  this->currentIndex_ = 0;
}

Option OptionIterator::firstOption() {
  currentIndex_ = 0;
  return (*optionCollection)[currentIndex_];
}

Option OptionIterator::nextOption() {
  currentIndex_ += 1;
  if (isDone() == false) {
    return (*optionCollection)[currentIndex_];
  } else {
    Option o;
    return o;
  }
}

Option OptionIterator::currentOption() {
  return (*optionCollection)[currentIndex_];
}

bool OptionIterator::isDone() {
  if (currentIndex_ < optionCollection->count()) {
    return false;
  }
  return true;
}
