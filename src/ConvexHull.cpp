#include <ConvexHull.h>
#include <UntwistLine.h>
#include <stack>

vector<Position> ConvexHull::getConvexHull(vector<Position>& points)
{
	UntwistLine::untwistLine(points);

	stack<int> convexHullIdx;

	convexHullIdx.push(0);
	convexHullIdx.push(1);

	int nextPointIdx = 2;
	
	// 모든 점 탐색
	while (nextPointIdx < points.size()) {
		while (convexHullIdx.size() >= 2) {
			int A, B;
			A = convexHullIdx.top();
			convexHullIdx.pop();
			B = convexHullIdx.top();
			// 최상단 점 2개와 다음점의 관계가 ccw일때까지 pop
			if (ccw(points[A], points[B], points[nextPointIdx]) < 0) {
				convexHullIdx.push(A);
				break;
			}
		}
		convexHullIdx.push(nextPointIdx++);
	}

	// convex hull을 구성하는 점들 저장
	vector<Position> convexHull;

	while (!convexHullIdx.empty()) {
		convexHull.push_back(points[convexHullIdx.top()]);
		convexHullIdx.pop();
	}

	return convexHull;
}

// 3점의 방향성을 알려줌
// 벡터 AB 와 벡터 AC의 CCW
// 반환값 ret > 0 : 반시계 방향, ret = 0 : 평행, ret < 0 시계방향
long long ConvexHull::ccw(const Position & A, const Position & B, const Position & C)
{
	const long long e = 1e6;
	long long ax = A.getLongitude() * e, ay = A.getLatitude() * e;
	long long bx = B.getLongitude() * e, by = B.getLatitude() * e;
	long long cx = C.getLongitude() * e, cy = C.getLatitude() * e;

	return (bx - ax) *(cy - ay) - (by - ay)*(cx - ax);
}
