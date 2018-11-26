#include <Population.h>

Population::Population(Position pos)
	:pos(pos), degree(-1), dominatedCnt(0)
{
}

bool Population::operator<(const Population & A)
{
	if (degree < A.degree || crowdingDistance > A.crowdingDistance)
		return true;
	return false;
}
