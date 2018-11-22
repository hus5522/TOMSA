#include<NSGA2.h>
#include<climits>

/*
* 파레토 최적해를 구함
*/
vector<set<int>> NSGA2::fastNondominatedSort(vector<vector<int>>& times)
{
	int objFuncCnt = times.size();
	set<int> *dominationSet = new set<int>[objFuncCnt];
	int *dominatedCnt = new int[objFuncCnt]();

	vector<set<int>> front;
	front.push_back(set<int>());

	for (int i = 0; i < objFuncCnt; i++) {
		for (int j = 0; j < objFuncCnt; j++) {
			vector<int> &p = times[i];
			vector<int> &q = times[j];
			if (dominates(p, q))
				dominationSet[i].insert(j);
			else if (dominates(q, p))
				dominatedCnt[i]++;
		}
		if (dominatedCnt[i] == 0)
			front[0].insert(i);
	}

	int sortDegree = 0;
	set<int> nondominatedFrontCandidate;
	while (front[sortDegree].size()) {

		for (int i = 0; i < front[sortDegree].size(); i++) {
			for (int j = 0; j < dominationSet[i].size(); j++) {
				dominatedCnt[j]--;
				if (dominatedCnt[j] == 0)
					nondominatedFrontCandidate.insert(j);
			}
		}
		sortDegree++;
		front.push_back(nondominatedFrontCandidate);
		nondominatedFrontCandidate.clear();
	}

	return front;
}

vector<vector<int>> NSGA2::crowdingDistanceAssignment(vector<vector<int>>& times, vector<set<int>> &front)
{
	int frontCnt = front.size();

	vector<vector<int>> dist(frontCnt);
	for (int deg = 0; deg < frontCnt; deg++) {
		int n = front[deg].size();
		dist.push_back(vector<int>(n));
		for (int i = 0; i < n; i++) {
			dist[deg][0] = dist[deg][n-1] = INT_MAX;

			for (int j = 1; j < n - 1; j++)
				dist[deg][j] = dist[deg][j] + (dist[deg][j + 1] - dist[deg][j - 1]) / (dist[deg][n - 1] - dist[deg][0]);
		}
	}

	return dist;
}

// f1 목적함수의 값이 f2 목적함수의 값을 지배하는지 판단
bool NSGA2::dominates(vector<int> &f1, vector<int> &f2)
{
	bool flg = false;
	for (int p : f1) {
		for (int q : f2) {
			if (p > q)
				return false;
			if (p < q)
				flg = true;
		}
	}

	return flg;
}

NSGA2::NSGA2(vector<Position>& users)
	:users(users)
{
}

NSGA2::~NSGA2()
{
	
}
