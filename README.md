#FE545-FinalProject

## About
This is a final project for FE545: Design Patterns and Derivatives Pricing. 

## Build
Under the root directory, using [make](http://unixhelp.ed.ac.uk/CGI/man-cgi?make) command will build whole project automatically.
```
$ make
```

## Dependencies
- [libcurl](http://curl.haxx.se/libcurl/)
- [jsoncpp](http://jsoncpp.sourceforge.net/)
- [boost](http://www.boost.org)


## Option Model

```
enum OptionType { CALL, PUT };
class Option {
	string stockName;
	string optionSymbol;
	double strikePrice;
	double purchasePrice;
	double optionPrice;	// ask
	OptionType optionType;
	boost::gregorian::date purchaseDate;
	boost::gregorian::date expirationDate;
}
```

##note

http://finance.google.com/finance/info?client=ig&q=

For current stock price, use this simple google finance api. 

