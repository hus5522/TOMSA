#ifndef __CTC_H__
#define __CTC_H__

#include "Position.h"
#include <vector>

class ConcavetToConvex {

private:
	std::vector<Position> polygonPositions;

public:
	ConcavetToConvex();
	std::vector<Position> convert(std::vector<Position> &polygonPositions);
};

#endif

