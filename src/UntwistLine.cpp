#include "UntwistLine.h"
#include <cmath>
#include <utility>
#include <algorithm>
#include <Geolocation.h>

void UntwistLine::untwistLine(vector<Position> &points)
{
	vector<pair<double, Position>> degRank;

	// 제일 왼쪽에 있는 좌표를 뽑아 기준으로 만듬
	int minLonIdx = getMinLongitudeIdx(points);
	Position basePoint = points[minLonIdx];

	for (int i = 0; i < points.size(); i++) {
		if (minLonIdx == i)
			continue;
		double degree = calcTwoPointsDegree(basePoint, points[i]);
		degRank.push_back({ degree, points[i] });
	}
	// 각도 순 정렬
	sort(degRank.begin(), degRank.end());

	// 재구성된 점들로 points에 등록
	points[0] = basePoint;
	for (int i = 1; i < points.size(); i++)
		points[i] = degRank[i - 1].second;
}

/* 두 점사이의 각도 구하기
 */
double UntwistLine::calcTwoPointsDegree(const Position &pos1, const Position &pos2)
{
	double a = atan2(pos2.getLatitude() - pos1.getLatitude(),
		pos2.getLongitude() - pos1.getLongitude());
	return Geolocation::radiusToDegree(a);
}

int UntwistLine::getMinLongitudeIdx(const vector<Position>& points)
{
	int minLonIdx = 0;

	for (int i = 1; i < points.size(); i++)
		if (points[minLonIdx].getLongitude() > points[i].getLongitude())
			minLonIdx = i;
	return minLonIdx;
}
