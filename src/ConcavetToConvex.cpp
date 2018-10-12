#include "ConcavetToConvex.h"
#include "PointInPolygonAlgorithm.h"

ConcavetToConvex::ConcavetToConvex()
{
}

std::vector<Position> ConcavetToConvex::convert(std::vector<Position> &polygonPoints)
{
	PointInPolygonAlgorithm PIPAlgorithm;
	Position target;

	for (std::vector<Position>::size_type i = 0; i < polygonPoints.size();) {
		target = polygonPoints[i];
		polygonPoints.erase(polygonPoints.begin() + i);

		if (!PIPAlgorithm.isInside(target, polygonPoints)) {
			polygonPoints.insert(polygonPoints.begin() + i, target);
			i++;
		}
	}

	return polygonPoints;
}
