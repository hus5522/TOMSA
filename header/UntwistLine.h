#ifndef __UNTWISTLINE_H__
#define __UNTWISTLINE_H__

#include <Position.h>
#include <vector>

using namespace std;

class UntwistLine
{
public:
	static void untwistLine(vector<Position> &points);

private:
	static double calcTwoPointsDegree(const Position &pos1, const Position &pos2);
	static int getMinLongitudeIdx(const vector<Position> &points);
};

#endif
