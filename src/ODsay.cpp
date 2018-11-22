#include <ODsay.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <Geolocation.h>

string ODsay::getPathInfo(const Position &src, const Position &dest)
{
	const wchar_t *subUri = L"/v1/api/searchPubTransPath";    

	// 요청 보낼 주소 및 인자 설정
    http_client client(baseUri);
    uri_builder builder(subUri);

    builder.append_query(U("SX"), src.getLongitude());
    builder.append_query(U("SY"), src.getLatitude());
    builder.append_query(U("EX"), dest.getLongitude());
    builder.append_query(U("EY"), dest.getLatitude());
    builder.append_query(U("apiKey"), apiKey);

	string pathInfo;	// 요청에 대한 결과값을 저장할 변수

	// ODsay api로 요청
	client.request(methods::GET, builder.to_string())
		.then([](http_response response) {
		return response.extract_string();
	}).then([&](string_t str) {
		pathInfo = conversions::to_utf8string(str);
	}).wait();

    return pathInfo;
}

int ODsay::getPathMinTime(const Position &src, const Position &dest)
{
	string jsonPathInfo = getPathInfo(src, dest);

	rapidjson::Document document;
	document.Parse(jsonPathInfo.c_str());

	int minTime;
	try {
		//result값 있는지 확인
		if (!document.HasMember("result"))
			throw document["error"]["code"].GetString();	// error 코드 번호 던짐
		// 최소 시간 가져오기
		minTime = document["result"]["path"][0]["info"]["totalTime"].GetInt();
	}
	catch (const char* exception) {
		const int walkingDistPerMinute = 66.6;	// 분당 걸은 거리
		// 위도 경도 거리를 계산하여 도보시간 구함
		minTime = Geolocation::computeDistanceTwoPos(src, dest) * walkingDistPerMinute;
		cout << "ODsay exception : " << exception << endl;
	}

    return minTime;
}
