#include <TOMSA.h>
#include <PointInPolygonAlgorithm.h>
#include <ODsay.h>
#include <math.h>
#include <utility>
#include <algorithm>
#include <ConcaveToConvex.h>
#include <UntwistLine.h>
#include <random> // 첫 세대의 좌표점들을 구하기 위함
#include <time.h> //srand(time(NULL));
#include <iostream> //cout 이 모호하다고 떠서 넣음
#include <codecvt> // utf-8 -> 한글 변환
#include <math.h>

#define END_GENERATION 5 // 몇 세대까지 진행 할 것인가
#define POPULATION 10 // 몇 개의 유전자를 생성할 것인가.

TOMSA::TOMSA(vector<Position> points)
	:users(points)
{
	// 꼬여있는 다각형 풀기
	UntwistLine::untwistLine(points);
	// user 위치의 추천 범위 설정
	boudaryPoints = ConcaveToConvex::convert(points);
}


/* 입력된 유저들 좌표와 이동시간에 기반하여 중간값을 찾는 알고리즘
* return Position : 최적의 중간 좌표 값
*/
Position TOMSA::start()
{
	const bool NOT_INSIDE = false;
	double latVector = 0, lonVector = 0;		// 중간값에 대한 벡터들의 합 저장
	int consideredUserCnt = users.size();	// 고려해야 될 유저 수
	int generation = 1; //세대수 체크
	Position gene[POPULATION]; //현재 세대의 정보를 저장할 배열
	int greatSolution = 0; // 최적해의 인덱스
	double avgLat = 0.0, avgLng = 0.0;

	PointInPolygonAlgorithm PIPAlgorithm;

	/* 중간지점을 잡고, 더하거나 뺴면 보이지않는 원 안에서 랜덤으로 발생*/
	Position center = getCenterOfGravity();

	srand(time(NULL));
	
	for (int i = 0; i < POPULATION; i++) {
		gene[i].setLatitude(center.getLatitude() + ((rand() << 8) / 1000000.0));
		gene[i].setLatitude(gene[i].getLatitude() - ((rand() << 8) / 1000000.0));
		gene[i].setLongitude(center.getLongitude() + ((rand() << 8) / 1000000.0));
		gene[i].setLongitude(gene[i].getLongitude() - ((rand() << 8) / 1000000.0));

		// 영역 밖에 벗어났는지 확인
		if (PIPAlgorithm.isInside(gene[i], boudaryPoints) == NOT_INSIDE) {
			// 다시 구하기
			i -= 1;
		}
	}
	
	Position nextGene[POPULATION]; // 다음세대들 저장할 배열

	//각 유저에 대한 유전자 까지의 시간을 저장할 2차원 동적배열 선언
	int **time;
	time = new int*[consideredUserCnt];

	for (int i = 0; i < consideredUserCnt; i++) {
		*(time + i) = new int[POPULATION];
	}


	while (true) 
	{
		int usercount = 0;

		// END_GENERATION에 해당하는 세대까지 진행.
		if (generation == END_GENERATION) {
			cout << END_GENERATION << "세대에서 종료합니다" << endl;
			cout << "< " << END_GENERATION << "세대 유전자들의 지점까지 걸리는 시간들 >" << endl;
			for (Position point : users) {
				for (int i = 0; i < POPULATION; i++) {
					cout << time[usercount][i] << "분  ";
				}
				cout << endl;
				usercount++;
			}
			exit(1); //종료
		}

		cout << generation << "번째 세대 유전자들" << endl;
		for (int i = 0; i < POPULATION; i++) {
			cout.precision(6);
			cout << fixed << "{ \"latitude\": " << gene[i].getLatitude()
				<< ", \"longitude\": " << gene[i].getLongitude() << " }" << endl;
		}

		//시간 초기화
		**time = { 0, };
		
		// 각 사용자들의 위치에서 각 유전자들 좌표까지 가는데 걸리는 시간 구하기
		for (Position point : users) {

			for (int i = 0; i < POPULATION; i++) {
				time[usercount][i] = getPathTime(point, gene[i]);
				cout << (usercount + 1) << "번째 유저가 " << i+1 << "번째 유전자 좌표까지 가는데 걸린 시간 : " << time[usercount][i] << endl;
			}

			usercount++;
		}

		//이번세대에 최적해가 존재하는지 확인 -> 존재하면 반환하고 종료
		if (isOptimizedResult(time, consideredUserCnt, &greatSolution)) {
			/* 경로에 대한 것을 string으로..
			usercount = 0;
			cout << "< 최종 결과 >" << endl;
			for (Position point : users) {
				
				//??????
				std::wstring_convert < std::codecvt_utf8_utf16<wchar_t>> convert;
				std::wstring path = convert.from_bytes(convert);
				

				//한글 깨짐 현상 발생 
				cout << usercount + 1 << "번째 사용자가 목적지 까지 가는 경로" << endl << getPath(point, gene[greatSolution]) << endl;
				usercount++;
			}
			*/
			return gene[greatSolution];
		}

		// 유전자 세대 바꾸기
		for (int i = 0; i < POPULATION; i++) {
			if (i == (rand() % POPULATION)) {
				nextGene[i] = gene[i]; // 다음 세대로 가기를 선택받은 놈들
			}
			else { // 돌연변이 생성
				if (rand() % 2) {
					nextGene[i].setPosition(gene[i].getLatitude() + ((rand() % 10000) / 200000.0), gene[i].getLongitude() + ((rand() % 10000) / 200000.0) );
				}
				else {
					nextGene[i].setPosition(gene[i].getLatitude() - ((rand() % 10000) / 200000.0), gene[i].getLongitude() - ((rand() % 10000) / 200000.0));
				} //if-else in else
			}// if-else
		}//for i

		// 영역 밖에 벗어났는지 확인
		// TODO : 벗어났을때 좌표를 어디로 옮길지 생각해야됨
		for (int i = 0; i < POPULATION; i++) {
			if (PIPAlgorithm.isInside(nextGene[i], boudaryPoints) == NOT_INSIDE) {
				// 벗어난 다음세대들의 좌표가 있으면 다시구하기.
				if (rand() % 2) {
					nextGene[i].setPosition(gene[i].getLatitude() + ((rand() % 10000) / 200000.0), gene[i].getLongitude() + ((rand() % 10000) / 200000.0));
				}
				else {
					nextGene[i].setPosition(gene[i].getLatitude() - ((rand() % 10000) / 200000.0), gene[i].getLongitude() - ((rand() % 10000) / 200000.0));
				} //if-else in else
			}
		}

		/*
		else if (isOnWater()) {
			// 물 위라면 좌표 값을 어디로?
		}
		*/

		//다음 세대로 적용
		for (int i = 0; i < POPULATION; i++) {
			gene[i] = nextGene[i];
		}

		generation++; // 세대 증가

	}//while

	//할당 해제
	for (int i = consideredUserCnt - 1; i <= 0; i--) {
		delete[] * (time + i);
	}

	delete[] time;
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

/* 출발지에서 목적지 까지 가는 경로 반환 */
string TOMSA::getPath(const Position &src, const Position &dest) {
	return odsay.getPathInfo(src, dest);
}


/* 찾은 중간 값이 최적화된 결과인지 판별하는 메소드
 * MIN_TIME_INTERVAL 간격에 속하는 유저들을 그룹화 하여
 * 특정 인원이 그룹에 속해있다면 최적화 되었다 판단
 * parameters -> times : 유저들의 이동시간, userCnt : 만족해야될 유저 수
 * return true/false 
 */
bool TOMSA::isOptimizedResult(vector<int> times, int userCnt)
{
	// 그룹화될 유저들의 이동시간의 범위
	const int MIN_TIME_INTERVAL = 10;

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

bool TOMSA::isOptimizedResult(int **time, int userCnt, int *greatSolution)
{
	// 그룹화될 유저들의 이동시간의 범위
	const int MIN_TIME_INTERVAL = 5;

	//int minTimeOfGroup = -1;	// 해당 그룹안의 유저의 최소 이동시간
	int *minTimeOfGroup = new int[POPULATION];
	//int userCntInGroup = 0;		// 한 그룹으로 묶여있는 유저 수
	int *maxTimeOfGroup = new int[POPULATION];

	for (int i = 0; i < POPULATION; i++) {
		*(minTimeOfGroup + i) = 999;
		*(maxTimeOfGroup + i) = 0;
	}
	
	for (int j = 0; j < POPULATION; j++) {
		for (int i = 0; i < userCnt; i++) {

			//최소시간 저장
			if (time[i][j] < minTimeOfGroup[j])
				minTimeOfGroup[j] = time[i][j];

			//최대시간 저장
			if (time[i][j] > maxTimeOfGroup[j])
				maxTimeOfGroup[j] = time[i][j];

		} //for i
	}//for j

	for (int i = 0; i < POPULATION; i++) {
		//최대시간 - 최소시간 = 3분 이하면 최적해임 -> 종료
		if ((maxTimeOfGroup[i] - minTimeOfGroup[i]) <= MIN_TIME_INTERVAL) {
			*greatSolution = i;
			return true;
		}
	}

	delete[] maxTimeOfGroup;
	delete[] minTimeOfGroup;

	return false;
}