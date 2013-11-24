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
- [jansson](http://www.digip.org/jansson/)


## Option structure

```
option {
  String stockName;
  double strikePrice;
  double stockPrice;
  double optionPrice;
  Type optionType;
  date purchaseDate;
  date expirationDate;
}
```


