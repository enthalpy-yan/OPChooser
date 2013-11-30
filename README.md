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
## API Reference

### Helper Class

- GET_STOCK_PRICE(stock_name)
    
    Returns the price of stock given in stock_name.
    ```
	double price = GET_STOCK_PRICE("GOOG")	 => get the price of GOOG.
    ```

- GET_OPTIONS(stock_name, expiration_date, option_type)

    Returns the options list with the given arguments.
    ```
	OptionCollection optionList = GET_OPTIONS("GOOG", "2013-12", CALL) => get all of GOOG's option(Type: call, expiration date: before 2013-12).
    ```

- SEND_HTTP_REQUEST(request_url)
    
    Returns the response(string) of url given in request_url. Only HTTP GET method.
    ```
	SEND_HTTP_REQUEST("http://www.example.org")
    ```


### Logger Class

- DEBUG_CONF(logfile_name, configuraitons, fileVerbosityLevel, screenVerbosityLevel)

    Configures the logger.
    ```
	DEBUG_CONF("outputfile", Logger::file_on|Logger::screen_on, DEBUG_FLAG, ERROR_FLAG) => log debug info in logfile and error info on screen.
	DEBUG_CONF("", Logger::screen_on, DEBUG_FLAG, DEBUG_FLAG) => log debug info on screen.
    ```
- DEBUG(log_flag, log_messages)

    Prints log messages.
    ```
	DEBUG(DEBUG_FLAG, "hello " << "world"); => log message "hello world".
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
  |  |- logger.h               (Header file for Logger class)
  |- source/
  |  |- main.cpp               (Main function)
  |  |- myAppHelper.cpp        (Implementation for Helper class)
  |  |- option.cpp             (Implementation for Option class)
  |  |- optionCollection.cpp   (Implementation for concreate Option Collection class)
  |  |- optionFactory.cpp      (Implementation for Option Factory class)
  |  |- optionIterator.cpp     (Implementation for concreate Option Iterator class)
  |  |- restclient.cpp         (Implementation for RestClient class)
  |  |- logger.cpp             (Implementation for Logger class)
  |- Makefile                  (Makefile for building this application)
  |- README.md                 (Readme file for github)
```
