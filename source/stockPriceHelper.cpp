#include "../include/stockPriceHelper.h"

const std::string StockPriceHelper::PREFIXURL = "http://finance.google.com/finance/info?client=ig&q=";

double StockPriceHelper::s_to_d(const std::string& strPrice) {
    return std::atof(strPrice.c_str());
}

double StockPriceHelper::getPrice(const std::string& stockName) {
    std::string targetUrl = PREFIXURL;
    targetUrl.append(stockName);
    RestClient::response r = RestClient::get(targetUrl);
    std::string responseJson = r.body;

    responseJson.erase(responseJson.begin(), responseJson.begin() + 5);
    responseJson.erase(responseJson.end() - 2, responseJson.end());

    Json::Value root;
    Json::Reader reader;
    bool parsedSuccess = reader.parse(responseJson, root, false);

    if (not parsedSuccess) {
        std::cout << "Failed to parse JSON" << std::endl << reader.getFormatedErrorMessages() << std::endl;
        exit(1);
    }

    // Print response in styled json.
    // std::cout << root.toStyledString() << std::endl;

    const Json::Value stockPrice = root["l_fix"];

    if (not stockPrice.isNull()) {
        return StockPriceHelper::s_to_d(stockPrice.asString());
    } else {
      exit(1);
    }
}