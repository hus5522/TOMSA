#ifndef __CONVEX_HULL__
#define __CONVEX_HULL__

#include <vector>
#include <Position.h>

using namespace std;

class ConvexHull
{
public:
	static vector<Position> getConvexHull(vector<Position> &points);

private:
	static long long ccw(const Position &A, const Position &B, const Position &C);
};

#endif