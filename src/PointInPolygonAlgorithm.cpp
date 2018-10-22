#include "PointInPolygonAlgorithm.h"

PointInPolygonAlgorithm::PointInPolygonAlgorithm()
{
}

bool PointInPolygonAlgorithm::isInside(const Position &target, const std::vector<Position> &polygonPoints)
{
	initPolygonLines(polygonPoints);

	int intersectTotalCnt = 0;
	for (Line line : polygonLines) {
		if (isIntersect(target, line))
			intersectTotalCnt++;
	}

	return intersectTotalCnt % 2 == 1;
}

void PointInPolygonAlgorithm::initPolygonLines(const std::vector<Position>& points)
{
	if(!polygonLines.empty())
		polygonLines.clear();

	int pointsCnt = points.size();
	for (int curPoint = 0; curPoint < pointsCnt; curPoint++) {
		int nextPoint = (curPoint + 1) % pointsCnt;
		polygonLines.push_back(Line(points[curPoint], points[nextPoint]));
	}
}

bool PointInPolygonAlgorithm::isIntersect(const Position &target, const Line &line) const
{
	const Position &src = line.getSrc();
	const Position &dest = line.getDest();

	if ((target.getLongitude() < src.getLongitude()) != (target.getLongitude() < dest.getLongitude())) {
		double intersectionPoint = (dest.getLatitude() - src.getLatitude())
			* (target.getLongitude() - src.getLongitude()) / (dest.getLongitude() - src.getLongitude())
			+ src.getLatitude();

		return target.getLatitude() < intersectionPoint;
	}
	return false;
}
