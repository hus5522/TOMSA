#ifndef __TOA_H__
#define __TOA_H__

#include <Position.h>
#include <vector>

class TimeOptimizationAlgorithm
{
private:
	std::vector<Position> users;

public:
	TimeOptimizationAlgorithm(std::vector<Position> &points);
	Position start();
	
private:	
	Position getCenterOfGravity();
	int getPathTime(Position src, Position dest);
	bool isOptimizedResult(std::vector<int> times, int userCnt);
};

#endif

