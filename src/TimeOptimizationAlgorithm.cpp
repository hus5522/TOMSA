#include <TimeOptimizationAlgorithm.h>
#include <PointInPolygonAlgorithm.h>
#include <math.h>
#include <utility>
#include <algorithm>
#include <node/node.h>
using namespace std;
TimeOptimizationAlgorithm::TimeOptimizationAlgorithm(std::vector<Position> &points)
	:users(points)
{
}

Position TimeOptimizationAlgorithm::start()
{
	Position midPoint = getCenterOfGravity();
	PointInPolygonAlgorithm PIPAlgorithm;

	const bool NOT_INSIDE = false;
	double lat = 0, lng = 0;
	int consideredUserCnt = users.size();

	std::vector<int> times;
	while (true)
	{	
		for (Position point : users) {
			int time = getPathTime(point, midPoint);
			times.push_back(time);

			lat += (point.getLatitude() - midPoint.getLatitude()) * time;
			lng += (point.getLongitude() - midPoint.getLongitude()) * time;
		}
		midPoint.setPosition(lat / users.size(), lng / users.size());

		if (PIPAlgorithm.isInside(midPoint, users) == NOT_INSIDE)
			consideredUserCnt--;
		else if (isOptimizedResult(times, consideredUserCnt))
			return midPoint;
	}
}

Position TimeOptimizationAlgorithm::getCenterOfGravity()
{
	double latitude = 0, longitude = 0;
	for (Position point : users) {
		latitude += point.getLatitude();
		longitude += point.getLongitude();
	}

	latitude /= users.size();
	longitude /= users.size();

	return Position(latitude, longitude);
}

int TimeOptimizationAlgorithm::getPathTime(Position src, Position dest)
{
	return 1;
}

bool TimeOptimizationAlgorithm::isOptimizedResult(std::vector<int> times, int userCnt)
{
	const int MIN_TIME_INTERVAL = 5;

	sort(times.begin(), times.end());

	int minTimeOfGroup = -1;
	int userCntOfGroup = 0;

	for (int time : times) {
		if (userCntOfGroup == 0) {
			minTimeOfGroup = time;
			userCntOfGroup++;
		}
		else if (minTimeOfGroup <= time && time <= minTimeOfGroup + MIN_TIME_INTERVAL)
			userCntOfGroup++;
		else {
			if (userCntOfGroup >= userCnt)
				break;
			userCntOfGroup = 0;
		}
	}
	
	if (userCntOfGroup >= userCnt)
		return true;
	return false;
}
