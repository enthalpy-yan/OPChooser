#FE545-FinalProject

## About
This is a final project for FE545: Design Patterns and Derivatives Pricing. 

## Build
Under the root directory
```
$ make
```

## Dependencies
- [libcurl](http://curl.haxx.se/libcurl/)    (handling http request and response)
- [jsoncpp](http://jsoncpp.sourceforge.net/) (parsing json format)
- [boost](http://www.boost.org)              (useful libraries)


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

## Overall Directory Structure

At a high level, the structure looks roughly like this:

```
FE545-FinalProject/
  |- include/
  |  |- iOptionCollection.h    (Interface for Option Collection) 
  |  |- iOptionIterator.h      (Interface for Option Iterator)
  |  |- myAppHelper.h          (Header file for Helper class)
  |  |- option.h               (Header file for Option model class) 
  |  |- optionCollection.h     (Header file for concreate Option Collection class)
  |  |- optionFactory.h        (Header file for Option Factory)
  |  |- optionIterator.h       (Header file for concreate Option Interator class) 
  |  |- restclient.h           (Header file for RestClient class)
  |- source/
  |  |- main.cpp               (Main function)
  |  |- myAppHelper.cpp        (Implementation for Helper class)
  |  |- option.cpp             (Implementation for Option class)
  |  |- optionCollection.cpp   (Implementation for concreate Option Collection class)
  |  |- optionFactory.cpp      (Implementation for Option Factory class)
  |  |- optionIterator.cpp     (Implementation for concreate Option Iterator class)
  |  |- restclient.cpp         (Implementation for RestClient class)
  |- Makefile                  (Makefile for building this application)
  |- README.md                 (Readme file for github)
```
