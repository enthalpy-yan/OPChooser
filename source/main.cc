#include <iostream>
#include "../include/restclient.h"

int main() {
    RestClient::response r = RestClient::get("http://example.com");
    std::cout << r.body << std::endl;
}
