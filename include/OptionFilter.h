#ifndef _OPTION_FILTER_H_
#define _OPTION_FILTER_H_

#include <vector>

#include "MyAppHelper.h"

class OptionFilter {
protected:
	OptionCollection originCall_;
	OptionCollection originPut_;
	std::vector<Option> call_;
	std::vector<Option> put_;
	std::vector<Option> secondResult_;
	std::vector<Option> result_;

public:
	std::vector<Option> filter();
	virtual void doFirstCheck() = 0;
	virtual void doSecondCheck() = 0;
	virtual void doThirdCheck() = 0;
};

#endif