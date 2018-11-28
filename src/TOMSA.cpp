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
	// ��� ���� ����
	boudaryPoints = ConvexHull::getConvexHull(points);
}


/* �Էµ� ������ ��ǥ�� �̵��ð��� ����Ͽ� �߰����� ã�� �˰���
* return Positionnn : ������ �߰� ��ǥ ��
*/
Position TOMSA::start()
{
	const bool NOT_INSIDE = false;
	double latVector = 0, lonVector = 0;		// �߰����� ���� ���͵��� �� ����
	int consideredUserCnt = users.size();	// ����ؾ� �� ���� ��

	Position midPoint = getCenterOfGravity();
	PointInPolygonAlgorithm PIPAlgorithm;

	vector<int> movingTimes;	// �������� �̵��ð� ����
	int avgTime = 0;
	int gen = 1;
	while (gen <= 20) 
	{	
		if (gen++ % 10 == 0)
			MIN_TIME_INTERVAL += 5;

		movingTimes.clear();
		avgTime = 0;

		// ���� �߰� ��ǥ������ �̵��ð� ���ϱ�, ���� ��ǥ�� �̵��ϱ����� ���� ���
		for (Position point : users) {
			int time = getPathTime(point, midPoint);
			movingTimes.push_back(time);
			
			// vector �� ���ϱ�
			Position unitVector = getUnitVector(point, midPoint);
			latVector += unitVector.getLatitude() * time;
			lonVector += unitVector.getLongitude() * time;

			avgTime += time;
		}
		avgTime /= users.size();
		latVector /= (avgTime * users.size());
		lonVector /= (avgTime * users.size());
		
		// ���� �߰� ��ǥ�� ������ ������� �Ǵ�
		if (isOptimizedResult(movingTimes, consideredUserCnt))
			return midPoint;

		// �߰���ǥ �̵�
		midPoint.setPosition(midPoint.getLatitude()  + latVector / users.size(),
			midPoint.getLongitude() + lonVector / users.size());

		// ���� �ۿ� ������� Ȯ��
		// TODO : ������� ��ǥ�� ���� �ű��� �����ؾߵ�
		if (PIPAlgorithm.isInside(midPoint, boudaryPoints) == NOT_INSIDE) {
			// ����� �ϱ����� �����߽� ������ �ʱ�ȭ
			midPoint = getCenterOfGravity();
			consideredUserCnt--;
		}
	}
}

/* �����߽� ��ǥ ���ϱ�
 * return Position : �����߽� ��ǥ
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

/* �ּ� �̵� ��� �ð��� ã�� ��ȯ
 * parameters -> src : ���� ��ǥ, dest : ������ ��ǥ
 * return int : �ּҽð�
 */
int TOMSA::getPathTime(const Position &src, const Position &dest)
{
	return odsay.getPathMinTime(src, dest);
}


/* ã�� �߰� ���� ����ȭ�� ������� �Ǻ��ϴ� �޼ҵ�
 * MIN_TIME_INTERVAL ���ݿ� ���ϴ� �������� �׷�ȭ �Ͽ�
 * Ư�� �ο��� �׷쿡 �����ִٸ� ����ȭ �Ǿ��� �Ǵ�
 * parameters -> times : �������� �̵��ð�, userCnt : �����ؾߵ� ���� ��
 * return true/false 
 */
bool TOMSA::isOptimizedResult(vector<int> times, int userCnt)
{
	sort(times.begin(), times.end());

	int minTimeOfGroup = -1;	// �ش� �׷���� ������ �ּ� �̵��ð�
	int userCntInGroup = 0;		// �� �׷����� �����ִ� ���� ��

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
