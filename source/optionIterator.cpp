#include "../include/OptionIterator.h"

OptionIterator::OptionIterator(IOptionCollection *oc) {
    this->optionCollection = oc;
    this->currentIndex_ = 0;
}

Option OptionIterator::FirstOption() {
    currentIndex_ = 0;
    return (*optionCollection)[currentIndex_];
}

Option OptionIterator::NextOption() {
    currentIndex_ += 1;
    if (IsDone() == false) {
        return (*optionCollection)[currentIndex_];
    } else {
        Option o;
        return o;
    }
}

Option OptionIterator::CurrentOption() {
    return (*optionCollection)[currentIndex_];
}

bool OptionIterator::IsDone() {
    if (currentIndex_ < optionCollection->Count()) {
        return false;
    }
    return true;
}