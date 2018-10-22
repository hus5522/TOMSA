#ifndef __CTC_H__
#define __CTC_H__

#include "Position.h"
#include <vector>

class ConcaveToConvex {

public:
	static std::vector<Position> convert(std::vector<Position> &polygonPositions);
};

#endif

