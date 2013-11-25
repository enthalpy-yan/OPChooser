#ifndef __OPTION_H_INCLUDED__
#define __OPTION_H_INCLUDED__
#include <string>
using namespace std;

enum OptionType { CALL, PUT };
class Option {
	string stockName;
	string optionSymbol;
	double strikePrice;
	double purchasePrice;
	double optionPrice;	// ask
	OptionType optionType;
	string purchaseDate;
	string expirationDate;


public:
	Option();
	Option(string stockName);
	~Option();

	void setStockName(string stockName);
	string getStockName();
	void setOptionSymbol(string optionSymbol);
	string getOptionSymbol();
	void setStrikePrice(double strikePrice);
	double getStrikePrice();
	void setPurchasePrice(double purchasePrice);
	double getPurchasePrice();
	void setOptionPrice(double optionPrice);
	double getOptionPrice();
	void setOptionType(OptionType type);
	OptionType getOptionType();
	void setPurchaseDate(string purchaseDate);
	string getPurchaseDate();
	void setExpirationDate(string expirationDate);
	string getExpirationDate();

};

#endif
