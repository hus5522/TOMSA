#ifndef __NSGA2_H__
#define __NSGA2_H__

#include <vector>
#include <Position.h>
#include <set>
#include <Population.h>

using namespace std;

class NSGA2
{
private:
	vector<Population> pop;		// 유전자 개수(g) * 목적함수의 값 개수(f) : (g*f) 배열
	const int maxGeneration = 50;	// 최대 유전 횟수
	const int geneCnt = 10;		//유전자 수

public:
	vector<vector<int>> fastNondominatedSort(vector<Population> &pop);	// 반환값 front
	vector<Population> calcCrowdingDistance(vector<Population> &pop, vector<vector<int>> &front);
	vector<Population> sortPopulation(vector<Population> &pop);
	bool dominates(Population &p, Population &q);		// p가 q를 지배하는지 판단
	vector<vector<int>> nsga2();

public:
	NSGA2(vector<Population> &pop);
	~NSGA2();
};


#endif