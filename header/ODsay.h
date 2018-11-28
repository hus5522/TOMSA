#ifndef __ODSAY_H_
#define __ODSAY_H_

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <Position.h>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams
using namespace std;

class ODsay
{
private:
	const string apiKey = "+l2drsr2yXqK+H7SHxhFuo8EF3vfOgpZlFGF2/lbkm8";
	const string baseUri = "https://api.odsay.com/";

    
public:
	string getPathInfo(const Position &src, const Position &dest);
    int getPathMinTime(const Position &src, const Position &dest);

};

#endif