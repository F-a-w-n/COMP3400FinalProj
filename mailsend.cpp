// mailsend.cpp - original code by Fawn Barisic - sends an email to a customer to notiy of an unpaid bill
#define CURL_STATICLIB
#include "./curl/curl.h"
#include <iostream>

int main() {
    CURL *curl = curl_easy_init();
    if(curl) {
        std::cout << "Success! libcurl version: " << curl_version() << std::endl;
        curl_easy_cleanup(curl);
    }
    return 0;
}