#ifndef __PIP_H__
#define __PIP_H__

#include "Position.h"
#include "Line.h"
#include <vector>
#include <iostream>

class PointInPolygonAlgorithm {

private:
	std::vector<Line> polygonLines;

public:
	PointInPolygonAlgorithm();
	bool isInside(const Position &target, const std::vector<Position> &polygonPoints);


private:
	void initPolygonLines(const std::vector<Position> &points);
	bool isIntersect(const Position &target, const Line &line) const;
};

#endif