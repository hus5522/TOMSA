#include <TOMSA.h>
#include <PointInPolygonAlgorithm.h>
#include <ODsay.h>
#include <cmath>
#include <utility>
#include <algorithm>
#include <UntwistLine.h>
#include <ConvexHull.h>

TOMSA::TOMSA(vector<Position> points)
	:users(points)
{
	// 경계 범위 설정
	boudaryPoints = ConvexHull::getConvexHull(points);
}


/* 입력된 유저들 좌표와 이동시간에 기반하여 중간값을 찾는 알고리즘
* return Positionnn : 최적의 중간 좌표 값
*/
Position TOMSA::start()
{
	const bool NOT_INSIDE = false;
	double latVector = 0, lonVector = 0;		// 중간값에 대한 벡터들의 합 저장
	int consideredUserCnt = users.size();	// 고려해야 될 유저 수

	Position midPoint = getCenterOfGravity();
	PointInPolygonAlgorithm PIPAlgorithm;

	vector<int> movingTimes;	// 유저들의 이동시간 저장
	int avgTime = 0;
	int gen = 1;
	while (gen <= 20) 
	{	
		if (gen++ % 10 == 0)
			MIN_TIME_INTERVAL += 5;

		printf("%lf, %lf\n", midPoint.getLatitude(), midPoint.getLongitude());
		movingTimes.clear();
		avgTime = 0;

		// 현재 중간 좌표까지의 이동시간 구하기, 다음 좌표로 이동하기위한 벡터 계산
		for (Position point : users) {
			int time = getPathTime(point, midPoint);
			movingTimes.push_back(time);
			
			// vector 값 더하기
			Position unitVector = getUnitVector(point, midPoint);
			latVector += unitVector.getLatitude() * time;
			lonVector += unitVector.getLongitude() * time;

			avgTime += time;
		}
		avgTime /= users.size();
		latVector /= (avgTime * users.size());
		lonVector /= (avgTime * users.size());

		for (int t : movingTimes)
			printf("%d ", t);
		printf("\n");
		

		// 현재 중간 좌표가 최적의 결과인지 판단
		if (isOptimizedResult(movingTimes, consideredUserCnt))
			return midPoint;

		// 중간좌표 이동
		midPoint.setPosition(midPoint.getLatitude()  + latVector / users.size(),
			midPoint.getLongitude() + lonVector / users.size());

		// 영역 밖에 벗어났는지 확인
		// TODO : 벗어났을때 좌표를 어디로 옮길지 생각해야됨
		if (PIPAlgorithm.isInside(midPoint, boudaryPoints) == NOT_INSIDE) {
			// 재시작 하기위해 무게중심 값으로 초기화
			midPoint = getCenterOfGravity();
			consideredUserCnt--;
			printf("중간으로~~~\n");
		}
	}
}

/* 무게중심 좌표 구하기
 * return Position : 무게중심 좌표
 */
Position TOMSA::getCenterOfGravity()
{
	double latitude = 0, longitude = 0;
	for (Position point : users) {
		latitude += point.getLatitude();
		longitude += point.getLongitude();
	}

	latitude /= users.size();
	longitude /= users.size();

	return Position(latitude, longitude);
}

/* 최소 이동 경로 시간을 찾아 반환
 * parameters -> src : 시작 좌표, dest : 목적지 좌표
 * return int : 최소시간
 */
int TOMSA::getPathTime(const Position &src, const Position &dest)
{
	return odsay.getPathMinTime(src, dest);
}


/* 찾은 중간 값이 최적화된 결과인지 판별하는 메소드
 * MIN_TIME_INTERVAL 간격에 속하는 유저들을 그룹화 하여
 * 특정 인원이 그룹에 속해있다면 최적화 되었다 판단
 * parameters -> times : 유저들의 이동시간, userCnt : 만족해야될 유저 수
 * return true/false 
 */
bool TOMSA::isOptimizedResult(vector<int> times, int userCnt)
{
	sort(times.begin(), times.end());

	int minTimeOfGroup = -1;	// 해당 그룹안의 유저의 최소 이동시간
	int userCntInGroup = 0;		// 한 그룹으로 묶여있는 유저 수

	for (int time : times) {
		if (userCntInGroup == 0) {
			minTimeOfGroup = time;
			userCntInGroup++;
		}
		else if (time <= minTimeOfGroup + MIN_TIME_INTERVAL)
			userCntInGroup++;
		else
			userCntInGroup = 0;

		if (userCntInGroup >= userCnt)
			break;
	}

	if (userCntInGroup >= userCnt)
		return true;
	return false;
}

Position TOMSA::getUnitVector(const Position & src, const Position & dest)
{
	double latVector = src.getLatitude() - dest.getLatitude();
	double lonVector = src.getLongitude() - dest.getLongitude();
	double unitVectorLen = sqrt(pow(latVector, 2)
		+ pow(lonVector, 2));

	return Position(latVector / unitVectorLen / 10, lonVector / unitVectorLen / 10);
}
