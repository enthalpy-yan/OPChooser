#include "OptionFilter.h"

std::vector<Option> OptionFilter::filter(){
	LOGGER(DEBUG_FLAG, "Doing filter...");
	doFirstCheck();
	doSecondCheck();
	doThirdCheck();
	LOGGER(DEBUG_FLAG, "filter done...");
	return result_;
}