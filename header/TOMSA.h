#ifndef __TOA_H__
#define __TOA_H__

#include <Position.h>
#include <vector>
#include <ODsay.h>

using namespace std;

class TOMSA
{
private:
	vector<Position> users;
	vector<Position> boudaryPoints;

public:
	ODsay odsay;

public:
	TOMSA(std::vector<Position> points);
	Position start();
	
private:	
	Position getCenterOfGravity();
	int getPathTime(const Position &src, const Position &dest);
	string getPath(const Position &src, const Position &dest);
	bool isOptimizedResult(vector<int> times, int userCnt);
	bool isOptimizedResult(int **time, int userCnt, int* greatSolution);
};

#endif

