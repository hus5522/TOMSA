#include<NSGA2.h>
#include<climits>
#include<algorithm>
#include<functional>


vector<vector<int>> NSGA2::fastNondominatedSort(vector<Population> &pop)
{
	int geneCnt = pop.size();

	for (Population p : pop) {
		p.dominationSet.clear();
		p.dominatedCnt = 0;
	}

	vector<vector<int>> front(1);

	for (int i = 0; i < geneCnt; i++) {
		for (int j = i + 1; j < geneCnt; j++) {
			Population &p = pop[i];
			Population &q = pop[j];
			if (dominates(p, q)) {
				p.dominationSet.push_back(j);
				q.dominatedCnt++;
			}
			else if (dominates(q, p)) {
				q.dominationSet.push_back(i);
				p.dominatedCnt++;
			}
		}
		if (pop[i].dominatedCnt == 0) {
			front[0].push_back(i);
			pop[i].degree = 0;
		}
	}

	int degree = 0;
	vector<int> nsCandidates;

	while (front[degree].size() > 0) {
		for (int i = 0; i < front[degree].size(); i++) {
			for (int j = 0; j < pop[i].dominationSet.size(); j++) {
				Population &q = pop[j];
				q.dominatedCnt--;

				if (q.dominatedCnt == 0) {
					nsCandidates.push_back(j);
					q.degree = degree + 1;
				}
			}
		}

		front.push_back(nsCandidates);
		degree++;

		nsCandidates.clear();
	}

	return front;
}

vector<Population> NSGA2::calcCrowdingDistance(vector<Population>& pop, vector<vector<int>>& front)
{
	int frontCnt = front.size();

	for (int i = 0; i < frontCnt; i++) {

		int objCostCnt = pop[i].cost.size();
		int nfrontCnt = front[i].size();

		vector<vector<int>> dist(nfrontCnt, vector<int>(objCostCnt, 0));

		for (int j = 0; j < objCostCnt; j++) {
			vector<pair<int, int>> obj(nfrontCnt);
			for (int k = 0; k < nfrontCnt; k++)
				obj[k] = { pop[front[i][j]].cost[k], k };
			sort(obj.begin(), obj.end());
			
			dist[obj[0].second][j] = dist[nfrontCnt - 1][j] = INT_MAX;

			for (int k = 1; k < nfrontCnt - 1; k++)
				dist[obj[k].second][j] += (obj[k + 1].first - obj[k - 1].first) / (obj[0].first - obj[nfrontCnt - 1].first);
		}

		for (int j = 0; j < nfrontCnt; j++) {
			int sumOfDist = 0;
			for (int k = 0; k < objCostCnt; k++)
				sumOfDist += dist[j][k];
			pop[front[i][j]].crowdingDistance = sumOfDist;
		}
	}

	return pop;
}

vector<Population> NSGA2::sortPopulation(vector<Population>& pop)
{
	vector<Population> sortOfCrwodingDistancePop = pop;
	sort(sortOfCrwodingDistancePop.begin(), sortOfCrwodingDistancePop.end());

	vector<Population> popNext;

	for (int i = 0; i < geneCnt; i++)
		popNext.push_back(sortOfCrwodingDistancePop[i]);

	return popNext;
}

bool NSGA2::dominates(Population & p, Population & q)
{
	bool flg = false;
	for (int pCost : p.cost) {
		for (int qCost : q.cost) {
			if (pCost > qCost)
				return false;
			if (pCost < qCost)
				flg = true;
		}
	}

	return flg;
}

vector<vector<int>> NSGA2::nsga2()
{
	// 파레토 최적 프론트
	vector<vector<int>> front = fastNondominatedSort(pop);
	// 프론트들의 각각 군집 거리
	vector<Population> dist = calcCrowdingDistance(pop, front);

	vector<Population> genes = sortPopulation(pop);


	return vector<vector<int>>();
}

NSGA2::NSGA2(vector<Population>& pop)
	:pop(pop)
{
}

NSGA2::~NSGA2()
{
	
}
