#include <iostream>
#include <cstdio>
#include <cstring>

#include "../include/restclient.h"
#include "json/json.h"

using namespace std;

int main() {
    RestClient::response r = RestClient::get("http://finance.google.com/finance/info?client=ig&q=GOOG");
    string responseJson = r.body;

    responseJson.erase(responseJson.begin(), responseJson.begin() + 5);
    responseJson.erase(responseJson.end() - 2, responseJson.end());

    Json::Value root;
    Json::Reader reader;
    bool parsedSuccess = reader.parse(responseJson, root, false);

    if (not parsedSuccess) {
        cout << "Failed to parse JSON" << endl << reader.getFormatedErrorMessages() << endl;
        return 1;
    }

    cout << root.toStyledString() << endl;

    const Json::Value stockPrice = root["l_fix"];

    if (not stockPrice.isNull()) {
        cout << "Price: " << stockPrice.asString() << endl;
    }

    /*
    for (unsigned int index=0; index<array.size(); ++index) {
        cout << array[index].asString() << endl;
    }
    */  

    return 0;
}
