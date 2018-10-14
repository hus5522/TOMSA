#include "ODsay.h"

int ODsay::getPathTime(Position src, Position dest)
{
    const string subUri = "/v1/api/searchPubTransPath";
    int PathTime;

    http_client client(baseUri);
    uri_builder builder(subUri);

    builder.append_query(U("SX"), U(src.getLongitude()));
    builder.append_query(U("SY"), U(src.getLatitude()));
    builder.append_query(U("EX"), U(dest.getLongitude()));
    builder.append_query(U("EY"), U(dest.getLatitude()));
    builder.append_query(U("apiKey"), apiKey);

    cout << builder.to_string() << endl;

    auto requestTask = client.request(methods::GET, builder.to_string())
    .then([=](http_response response)
    {
        return response.extract_string();
    }).then([&](string_t str)
    {
        PathTime = stoi(str);
    });

    // Wait for all the outstanding I/O to complete and handle any exceptions
    try
    {
        requestTask.wait();
    }
    catch (const std::exception &e)
    {
        printf("Error exception:%s\n", e.what());
    }
    return PathTime;
}