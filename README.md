# TOMSA(TimeOptimizationMidSearchAlgorithm)

## DamoYeo

### 문제해결기법 1조 프로젝트

## 개요
거리뿐만 아니라, 각 사용자의 위치에서 중간지점까지 대중교통으로 소요되는 시간도 고려하는 최적의 중간지점을 찾아내는 알고리즘을 만들자.


## 개발 언어 및 환경
* C++
* Ubuntu
* Visual Studio


## 사용된 알고리즘
* Graham's Scan : 바깥 이용자들의 위치를 이어 형성된 다각형의 범위를 구하기 위한 알고리즘

![Graham](./Image/Graham.PNG)

* Point in a polygon : 구해진 중간 지점의 좌표가 Graham's Scan 알고리즘으로 도출된 다각형 안에 있는지 확인하기 위한 알고리즘

![PointInPolygon](./Image/PointInPolygon.PNG)

* 무게중심 : 초기 중간지점의 좌표를 구하기 위함.

* 간단한 유전자 알고리즘 : 여러개의 표본에 대하여 특정 가중치 값를 가감해 나가면서 조건에 맞는 중간지점을 도출하기 위함

* 중간 지점 옮기기 : 도출된 중간지점으로부터 각 사용자까지의 벡터 값을 이용하여 새로운 중간 지점을 구함.

![Search](./Image/Search.PNG)


## 팀원
* 컴퓨터공학과 김태우 : 시간 가중치 기반 최적 경로 탐색 알고리즘 설계, C++ 코드를 Ubuntu 환경에서 이용할 수 있도록 설정, Point in a polygon 알고리즘 구현, 총괄
* 컴퓨터공학과 허유성 : 시간 가중치 기반 최적 경로 탐색 알고리즘 설계, Graham's Scan 알고리즘 구현, 유전자 알고리즘을 이용한 테스트 코드 구현


## 알고리즘 프로세스

![Process](./Image/Process.PNG)

![Process2](./Image/Process2.png)


## 어플 '다모여'의 데이터 흐름도

![Flow](./Image/Flow.png)


## 비고
다모여 프로젝트 제작과 병행하여 '시간 가중치 기반 효율적인 최적 경로 탐색 기법 연구' 라는 주제로 논문을 작성했고

2019년 10월 현재 심사중이며 심사에 통과할 시 한국융합학회의 12월 논문지에 게재 예정임.
