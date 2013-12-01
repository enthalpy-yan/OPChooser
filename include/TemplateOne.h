#ifndef _TEMPLATE_ONE_H_
#define _TEMPLATE_ONE_H_

#include <vector>

#include "OptionFilter.h"
#include "MyAppHelper.h"
#include "Option.h"

class TemplateOne : public OptionFilter {

public:
	TemplateOne(OptionCollection occ, OptionCollection ocp);
	~TemplateOne();

	void doFirstCheck();
	void doSecondCheck();
	void doThirdCheck();
};

#endif