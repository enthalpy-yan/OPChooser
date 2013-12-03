#OPChooser

## About
This is a final project for FE545: Design Patterns and Derivatives Pricing. 

## Build and Run
Under the root directory
```
$ make
$ OPChooser -h
Allowed options:
  -h [ --help ]         Print help messages.
  -v [ --verbose ]      Print words with verbosity.
  -o [ --output ] arg   Set logging output file.
  -t [ --ticker ] arg   Set the name of ticker.
  -d [ --date ] arg     Set expiration date for the given ticker.
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

### OptionCollection

##### This is a strcuture used to save option informations. Basically, it is a std::vector\<Option\>.

- getIterator()
    
   Returns a iterator for the collection.
   ```
	OptionCollection optionList = GET_OPTIONS("GOOG", "2013-12", CALL);	

	IOptionIterator *iter = optionList.getIterator();

  	for ( Option p = iter->firstOption(); iter->isDone() == false; p = iter->nextOption() ) {
		std::cout << p << std::endl;
  	}
   ```

### Helper Class

##### This is a wrapper class for the functions used to get stock/option related informations.

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

##### This is a logger class for logging informations.

- LOGGER_CONF(logfile_name, configuraitons, fileVerbosityLevel, screenVerbosityLevel)

    Configures the logger.
    ```
	LOGGER_CONF("outputfile", Logger::file_on|Logger::screen_on, DEBUG_FLAG, ERROR_FLAG) => log debug info in logfile and error info on screen.
	LOGGER_CONF("", Logger::screen_on, DEBUG_FLAG, DEBUG_FLAG) => log debug info on screen.
    ```
- LOGGER(log_flag, log_messages)

    Prints log messages.
    ```
	LOGGER(DEBUG_FLAG, "hello " << "world"); => log message "hello world".
    ```

## Overall Directory Structure

At a high level, the structure looks roughly like this:

```
FE545-FinalProject/
  |- include/
  |  |- IOptionCollection.h    (Interface for Option Collection) 
  |  |- IOptionIterator.h      (Interface for Option Iterator)
  |  |- MyAppHelper.h          (Header file for Helper class)
  |  |- Option.h               (Header file for Option model class) 
  |  |- OptionCollection.h     (Header file for concreate Option Collection class)
  |  |- OptionFactory.h        (Header file for Option Factory)
  |  |- OptionIterator.h       (Header file for concreate Option Interator class) 
  |  |- Restclient.h           (Header file for RestClient class)
  |  |- Logger.h               (Header file for Logger class)
  |  |- OptionFilter.h	       (Header file for options filter class)
  |  |- TemplateOne.h	       (Header file for Template Method class)
  |  |- Strategy.h	       (Header file for Strategy class)
  |- source/
  |  |- Main.cpp               (Main function)
  |  |- MyAppHelper.cpp        (Implementation for Helper class)
  |  |- Option.cpp             (Implementation for Option class)
  |  |- OptionCollection.cpp   (Implementation for concreate Option Collection class)
  |  |- OptionFactory.cpp      (Implementation for Option Factory class)
  |  |- OptionIterator.cpp     (Implementation for concreate Option Iterator class)
  |  |- Restclient.cpp         (Implementation for RestClient class)
  |  |- Logger.cpp             (Implementation for Logger class)
  |  |- OptionFilter.cpp       (Implementation for options filter class)
  |  |- TemplateOne.cpp	       (Implementation for Template Method class)
  |  |- Strategy.cpp	       (Implementation for Strategy class)
  |- Makefile                  (Makefile for building this application)
  |- README.md                 (Readme file for github)
```
