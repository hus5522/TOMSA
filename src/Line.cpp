#include "Line.h"

Line::Line(const Position &src, const Position &dest)
{
	this->src = src;
	this->dest = dest;
}

Position Line::getSrc() const
{
	return this->src;
}

Position Line::getDest() const
{
	return this->dest;
}
