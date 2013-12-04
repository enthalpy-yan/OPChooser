#include <math.h>

#include "TemplateOne.h"
#include "Logger.h"

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
	LOGGER(DEBUG_FLAG, "The first filter has been finished!");
}

void TemplateOne::doSecondCheck(){
	std::vector<Option>::iterator iterCall;
	std::vector<Option>::iterator iterPut;

	for( iterCall = call_.begin(), iterPut = put_.begin(); iterCall != call_.end();){
		boost::gregorian::date purchaseDate = boost::gregorian::from_simple_string((*iterCall).getPurchaseDate());
		boost::gregorian::date expirationDate = boost::gregorian::from_simple_string((*iterCall).getExpirationDate());
		boost::gregorian::date_period dp( purchaseDate, expirationDate );

		double a = (*iterCall).getOptionPrice() + (*iterCall).getStrikePrice() * exp(-0.08 * dp.length().days() / 365);
		double b = (*iterPut).getOptionPrice() + (*iterPut).getPurchasePrice();
		if(a == b){
			iterCall = call_.erase(iterCall);
			iterPut = put_.erase(iterPut);
			LOGGER(DEBUG_FLAG, "One group was deleted by second filter");
		} else {
			secondResult_.push_back(*iterCall);
			secondResult_.push_back(*iterPut);
			iterCall++;
			iterPut++;
		}
	}
	LOGGER(DEBUG_FLAG, "The second filter has been finished!");
}

void TemplateOne::doThirdCheck(){
	std::map< std::string, std::vector<Option> > resultMap;

	/*
	 * seprate options according to different expiration date.
	 */
	std::vector<Option>::iterator iter;

	for( iter = secondResult_.begin(); iter != secondResult_.end(); iter++){
		string date = (*iter).getExpirationDate();
		if( resultMap.find(date) == resultMap.end() ){
			std::vector<Option> newVector;
			newVector.push_back(*iter);
			resultMap[date] = newVector;

		} else {
			std::map< std::string, std::vector<Option> >::iterator it;
			it = resultMap.find(date);
			it->second.push_back(*iter);
		}
			
	}

	/*
	 * return a vector according to the user input.
	 */
	std::cout << "============================================" << endl;
	std::cout << " Please choose an expiration date from here " << endl << endl;
	std::map< std::string, std::vector<Option> >::iterator k;
	for(k = resultMap.begin(); k != resultMap.end(); k++)
		std::cout << "              " << k->first << std::endl;
	std::cout << "============================================" << endl;
	std::cout << " Please input one date: ";
	string input;
	std::cin >> input;

	while (!(resultMap.count(input) > 0)) {
		std::cout << " Invalid date, please input again: ";
		std::cin >> input;
	}

	result_ = resultMap.find(input)->second;
	
	LOGGER(DEBUG_FLAG, "The third filter has been finished!");
	// for (vector<Option>::iterator it = result_.begin() ; it != result_.end(); ++it)
	// 		std::cout << *it << endl;
}