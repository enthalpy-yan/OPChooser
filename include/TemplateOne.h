#ifndef _TEMPLATE_ONE_H_
#define _TEMPLATE_ONE_H_

#include "OptionFilter.h"
#include "myAppHelper.h"
#include "option.h"
#include <vector>

class TemplateOne : public OptionFilter {

public:
	TemplateOne(OptionCollection occ, OptionCollection ocp);
	~TemplateOne();

	void doFirstCheck();
	void doSecondCheck();
	void doThirdCheck();
};

#endif