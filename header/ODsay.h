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
	//const wchar_t *apiKey = L"+l2drsr2yXqK+H7SHxhFuo8EF3vfOgpZlFGF2/lbkm8";
	const wchar_t *apiKey = L"ySxpWRE1l7DtFXJWri9zaVtftQAzTkZOHmbupn6ukXo";
	const wchar_t *baseUri = L"https://api.odsay.com/";

    //string getPathInfo(const Position &src, const Position &dest);
public:
	string getPathInfo(const Position &src, const Position &dest);
    int getPathMinTime(const Position &src, const Position &dest);

};

#endif