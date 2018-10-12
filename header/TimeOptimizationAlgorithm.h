#ifndef __TOA_H__
#define __TOA_H__

#include <Position.h>
#include <vector>
#include <nan.h>

class TimeOptimizationAlgorithm
{
private:
	std::vector<Position> users;
	Nan::Callback cbGetTotalTime;
	v8::Isolate *isolate;

public:
	TimeOptimizationAlgorithm(std::vector<Position> &points,
		v8::Isolate *isolate, v8::Local<v8::Function> &cbGetTotalTime);
	Position start();
	
private:	
	Position getCenterOfGravity();
	int getPathTime(Position src, Position dest);
	bool isOptimizedResult(std::vector<int> times, int userCnt);
};

#endif

