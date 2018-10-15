#ifndef __ODSAY_H_
#define __ODSAY_H_

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include "Position.h"

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams
using namespace std;

class ODsay
{
private:
    const string apiKey = U("");
    const string baseUri = U("https://api.odsay.com/");

    string getPathInfo(const Position &src, const Position &dest);
public:
    int getPathMinTime(Position src, Position dest);

};

#endif