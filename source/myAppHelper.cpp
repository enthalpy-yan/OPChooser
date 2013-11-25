#include "../include/myAppHelper.h"

const std::string MyAppHelper::PREFIXURL = "http://finance.google.com/finance/info?client=ig&q=";

bool MyAppHelper::instanceFlag = false;

MyAppHelper* MyAppHelper::single = NULL;

MyAppHelper& MyAppHelper::getInstance() {
    if(!instanceFlag) {
        single = new MyAppHelper();
        instanceFlag = true;
        return *single;
    } else {
        return *single;
    }
}

/**
 * Convert string to double
 */
double MyAppHelper::s_to_d(const std::string& strPrice) {
    return std::atof(strPrice.c_str());
}

/**
 * Send http request to the target url and get the response.
 * @param  url 
 * @return response strings
 */
std::string MyAppHelper::httpGetRequest(const std::string& url) {
    RestClient::response r = RestClient::get(url);
    return r.body;
}

/**
 * Retrieve real time stock price.
 * @param  stockName name of the stock
 * @return stock price
 */
double MyAppHelper::getStockPrice(const std::string& stockName) {
    std::string targetUrl = PREFIXURL;
    targetUrl.append(stockName);
    std::string responseJson = httpGetRequest(targetUrl);


    //trim stock data in order to fit in json object.
    responseJson.erase(responseJson.begin(), responseJson.begin() + 5);
    responseJson.erase(responseJson.end() - 2, responseJson.end());

    Json::Value root; //will contains the root value(json object) after parsing.
    Json::Reader reader;
    bool parsedSuccess = reader.parse(responseJson, root, false);

    if (not parsedSuccess) {
        // report to the user the failure and their locations in the document.
        std::cout << "Failed to parse JSON" << std::endl << reader.getFormatedErrorMessages() << std::endl;
        exit(1);
    }

    // Print response in styled json.
    // std::cout << root.toStyledString() << std::endl;

    //Get the value of the member of root named 'l_fix'(stock price).
    const Json::Value stockPrice = root["l_fix"];

    if (not stockPrice.isNull()) {
        return MyAppHelper::s_to_d(stockPrice.asString());
    } else {
        exit(1);
    }
}
