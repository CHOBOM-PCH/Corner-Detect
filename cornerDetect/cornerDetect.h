#ifndef CORNERDETECT_H
#define CORNERDETECT_H

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <math.h>
#include <iostream>
#include "RANSAC_LineFittingAlgorithm.h"

#ifdef _DEBUG
        #pragma comment(lib,"opencv_core2413d.lib")
        #pragma comment(lib,"opencv_highgui2413d.lib")
        #pragma comment(lib,"opencv_imgproc2413d.lib")
#else
        #pragma comment(lib,"opencv_core2413.lib")
        #pragma comment(lib,"opencv_highgui2413.lib")
        #pragma comment(lib,"opencv_imgproc2413.lib")
#endif

#define PI 3.1415926
#define TRUE 1
#define FALSE 0
using namespace cv;

int cornerDetect(const char* route,//코너를 찾아낼 이미지 경로 //점을 찾음 1 아님 -1
	int* distanceX,//코너에서 카메라중심까지의 거리
	int* distnaceY,
	int* pointX,//찾아낸 코너점의 위치
	int* pointY,
	int detectSize,//찾게될 점의 떨어진 거리
	int detectNum,// 찾을 점의 개수
	bool viewLine = FALSE);//라인 표시 여부

float cornerLineAngle(InputArray _edgeImage,//선을 검사할 edge 이미지 //찾아낸 코너점에서 두선의 각도(degree:float)
	InputArray _src,// 원본 이미지
	OutputArray _dst,// 찾아낸 점 선등을 출력할 이미지
	int startPointX,//코너점의 시작
	int startPointY,
	int detectSize,//찾게될 점의 떨어진 거리
	int detectNum,// 찾을 점의 개수
	bool viewLine = FALSE,//코너점에서 시작된 두 선의 표시 여부(기본 표시않함 TRUE시 표시)
	bool viewDetectPoint = FALSE);//코너점에서 시작된 선위에 있는 점의 표시 여부

#endif