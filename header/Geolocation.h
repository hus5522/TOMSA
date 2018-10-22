#ifndef __GEOLOCATION_H__
#define __GEOLOCATION_H__

#include <Position.h>

#define PI 3.14159265358979323846

class Geolocation
{
public:

public:
	static double computeDistanceTwoPos(const Position &src, const Position &des);
	static double degreeToRadius(const double degree);
	static double radiusToDegree(const double radius);
};

#endif
