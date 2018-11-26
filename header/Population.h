#ifndef __POPULATION_H__
#define __POPULATION_H__

#include <Position.h>
#include <vector>

using namespace std;

class Population
{
public:
	Position pos;		// 유전자의 위치좌표
	int degree;
	int dominatedCnt;	// 이 유전자를 지배하는 다른 유전자의 수
	vector<int> cost;	// 각 사용자들로부터의 이동시간 비용
	vector<int> dominationSet;
	int crowdingDistance; // 군집간의 거리

	Population(Position pos);

	bool operator < (const Population &A);
};

#endif
