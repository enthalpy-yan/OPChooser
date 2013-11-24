#include "Option.h"

Option::Option() {}

Option::Option(string stockName){
	this->stockName = stockName;
}

Option::~Option(){

}

void Option::setStockName(string stockName){
	this->stockName = stockName;
}


string Option::getStockName(){
	return this->stockName;
}

void Option::setStrikePrice(double strikePrice){
	this->strikePrice = strikePrice;
}

double Option::getStrikePrice(){
	return this->strikePrice;
}

void Option::setPurchasePrice(double purchasePrice){
	this->purchasePrice = purchasePrice;
}

double Option::getPurchasePrice(){
	return this->purchasePrice;
}

void Option::setOptionPrice(double optionPrice){
	this->optionPrice = optionPrice;
}

double Option::getOptionPrice(){
	return this->optionPrice;
}

void Option::setOptionType(OptionType type){
	this->optionType = type;
}

OptionType Option::getOptionType(){
	return this->optionType;
}

void Option::setPurchaseDate(string purchaseDate){
	this->purchaseDate = purchaseDate;
}

string Option::getPurchaseDate(){
	return this->purchaseDate;
}

void Option::setExpirationDate(string expirationDate){
	this->expirationDate = expirationDate;
}

string Option::getExpirationDate(){
	return this->expirationDate;
}