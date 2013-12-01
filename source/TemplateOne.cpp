#include "TemplateOne.h"
#include "logger.h"
#include <math.h>

TemplateOne::TemplateOne(OptionCollection occ, OptionCollection ocp){
	originCall_ = occ;
	originPut_ = ocp;
}

void TemplateOne::doFirstCheck(){
	IOptionIterator *iter1 = originCall_.getIterator();
	IOptionIterator *iter2 = originPut_.getIterator();
	for ( Option p1 = iter1->firstOption(); iter1->isDone() == false; p1 = iter1->nextOption() ) {
		for( Option p2 = iter2->firstOption(); iter2->isDone() == false; p2 = iter2->nextOption() ){
			if( p1.getStrikePrice() == p2.getStrikePrice() && p1.getExpirationDate() == p2.getExpirationDate() ){
				call_.push_back(p1);
				put_.push_back(p2);
			}
		}
	}
	LOGGER(DEBUG_FLAG, "in doFirstCheck");
}

void TemplateOne::doSecondCheck(){
	std::vector<Option>::iterator iterCall;
	std::vector<Option>::iterator iterPut;
	for( iterCall = call_.begin(), iterPut = put_.begin(); iterCall != call_.end();){
		double a = (*iterCall).getOptionPrice() + (*iterCall).getStrikePrice() * exp(-0.07);
		double b = (*iterPut).getOptionPrice() + (*iterPut).getPurchasePrice();
		if(a == b){
			iterCall = call_.erase(iterCall);
			iterPut = put_.erase(iterPut);
			LOGGER(DEBUG_FLAG, "a == b");
		} else {
			result_.push_back(*iterCall);
			result_.push_back(*iterPut);
			iterCall++;
			iterPut++;
		}
	}
	LOGGER(DEBUG_FLAG, "in doSecondCheck");
}