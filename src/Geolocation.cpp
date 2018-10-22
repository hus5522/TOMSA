#include "Geolocation.h"
#include <cmath>

double Geolocation::computeDistanceTwoPos(const Position & src, const Position & dest)
{
	// 반환 값 : meter
	const int EARTH_RADIUS = 6371;		//지구 반지름

	double degLatitude = degreeToRadius(src.getLatitude() - dest.getLatitude());
	double degLongitude = degreeToRadius(src.getLongitude() - dest.getLongitude());

	double dist = pow(sin(degLatitude / 2), 2) +
		cos(degreeToRadius(src.getLatitude())) * cos(degreeToRadius(dest.getLatitude()))
		* sin(degLongitude / 2) * sin(degLongitude / 2);

	dist = 2 * atan2(sqrt(dist), sqrt(1 - dist)) * EARTH_RADIUS;

	return dist;
}

double Geolocation::degreeToRadius(const double degree)
{
	return degree * PI / 180.0;
}

double Geolocation::radiusToDegree(const double radius)
{
	return radius * 180.0 / PI;
}
