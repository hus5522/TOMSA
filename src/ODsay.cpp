#include "ODsay.h"
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>

string ODsay::getPathInfo(const Position &src, const Position &dest)
{
    const string subUri = "/v1/api/searchPubTransPath";
    string pathInfo;

    http_client client(baseUri);
    uri_builder builder(subUri);

    builder.append_query(U("SX"), U(src.getLongitude()));
    builder.append_query(U("SY"), U(src.getLatitude()));
    builder.append_query(U("EX"), U(dest.getLongitude()));
    builder.append_query(U("EY"), U(dest.getLatitude()));
    builder.append_query(U("apiKey"), apiKey);

    auto requestTask = client.request(methods::GET, builder.to_string())
    .then([=](http_response response) {
        return response.extract_string();
    }).then([&](string_t str) {
        pathInfo = str;
    });

    // Wait for all the outstanding I/O to complete and handle any exceptions
    try {
        requestTask.wait();
    }
    catch (const std::exception &e) {
        printf("Error exception:%s\n", e.what());
    }
    return pathInfo;
}

int ODsay::getPathMinTime(Position src, Position dest)
{
    string jsonPathInfo = getPathInfo(src, dest);

    rapidjson::Document document;
    document.Parse(jsonPathInfo.c_str());

    // 최소 시간 가져오기
    int minTime = document["result"]["path"][0]["info"]["totalTime"].GetInt();

    return minTime;
}