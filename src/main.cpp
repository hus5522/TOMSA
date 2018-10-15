#include <iostream>
#include <string>
#include <Position.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <ConcavetToConvex.h>
#include <PointInPolygonAlgorithm.h>
#include <TimeOptimizationAlgorithm.h>
#include <ODsay.h>

#include <algorithm>

using namespace std;

Position startAlgorithm(std::vector<Position> &positions)
{
    ConcavetToConvex CTCAlgorithm;
    // conver concavet to convex
    CTCAlgorithm.convert(positions);
    // 시간 최적화 알고리즘 초기화
    TimeOptimizationAlgorithm TOAlgorithm(positions);

    return TOAlgorithm.start();
}

void initPositions(vector<Position> &positions, char *jsonString)
{
    rapidjson::Document document;
    document.Parse(jsonString);

    assert(document["userArr"].IsArray());
    const rapidjson::Value &userArr = document["userArr"];
    assert(userArr.IsArray());

    for(auto &user : userArr.GetArray()){
        assert(user["latitude"].IsDouble());
        assert(user["longitude"].IsDouble());
        positions.push_back(Position(user["latitude"].GetDouble(),
            user["longitude"].GetDouble()));
    }

    sort(positions.begin(), positions.end());
}

int main(int argc, char *argv[])
{
    if(argc < 2){
        cout << "argument is few" << endl;
        exit(1);
    }
    cout << argv[1] << endl;

    
    vector<Position> positions;

    initPositions(positions, argv[1]);

    Position midPoint = startAlgorithm(positions);

    cout << "{ \"latitude\": " << midPoint.getLatitude()
        << ", \"longitude\": " << midPoint.getLongitude();

    return 0;
}