#ifndef __LINE_H__
#define __LINE_H__

#include "Position.h"

class Line {

private:
	Position src, dest;

public:
	Line(const Position &src, const Position &dest);
	Position getSrc() const;
	Position getDest() const;
};

#endif