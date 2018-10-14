#include <node/node.h> // 중요 1. header
#include <nan.h>
#include <iostream>
#include <string>
#include <Position.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <ConcavetToConvex.h>
#include <PointInPolygonAlgorithm.h>
#include <TimeOptimizationAlgorithm.h>
#include <algorithm>

// write json data example
void sendJsonObject(const v8::FunctionCallbackInfo<v8::Value> &args, Position midPoint)
{
    v8::Local<v8::Object> jsonObject = Nan::New<v8::Object>();

    v8::Local<v8::String> latitudeProp = Nan::New("latitude").ToLocalChecked();
    v8::Local<v8::String> longitudeProp = Nan::New("longitude").ToLocalChecked();

    v8::Local<v8::Value> latitudeValue = Nan::New(midPoint.getLatitude());
    v8::Local<v8::Value> longitudeValue = Nan::New(midPoint.getLongitude());

    Nan::Set(jsonObject, latitudeProp, latitudeValue);
    Nan::Set(jsonObject, longitudeProp, longitudeValue);

    args.GetReturnValue().Set(jsonObject);
}

Position startAlgorithm(std::vector<Position> &positions,
    v8::Isolate *isolate, v8::Local<v8::Function> &cbGetTotalTime)
{
    ConcavetToConvex CTCAlgorithm;
    // conver concavet to convex
    CTCAlgorithm.convert(positions);
    // 시간 최적화 알고리즘 초기화
    TimeOptimizationAlgorithm TOAlgorithm(positions, isolate, cbGetTotalTime);

    return TOAlgorithm.start();
}

void initPositions(const v8::FunctionCallbackInfo<v8::Value> &jsonObject,
    std::vector<Position> &positions)
{
    v8::String::Utf8Value v8_jsonString(jsonObject[0]);
    std::string jsonString(*v8_jsonString);

    rapidjson::Document document;
    document.Parse(jsonString.c_str());

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

// parse json data example
void TimeOptimizationCenterFindAlgorithm(const v8::FunctionCallbackInfo<v8::Value> &args)
{
    v8::Isolate* isolate = args.GetIsolate();
    // 콜백함수 설정
    v8::Local<v8::Function> cbFunction = v8::Local<v8::Function>::Cast(args[1]);
    
    std::vector<Position> positions;
    initPositions(args, positions);
    
    Position midPoint = startAlgorithm(positions, isolate, cbFunction);

    // 노드로 값 리턴
    sendJsonObject(args, midPoint);
}
    
void init(v8::Local<v8::Object> exports) { // 중요 3. Method 정의
    NODE_SET_METHOD(exports, "TOCFA", TimeOptimizationCenterFindAlgorithm);
}

NODE_MODULE(addon, init) // 중요 2. 모듈 정의