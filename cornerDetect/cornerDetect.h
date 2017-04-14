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

int cornerDetect(const char* route,
	int* distance,
	int* pointX,
	int* pointY);

float cornerLineAngle(InputArray _edgeImage,
	InputArray _src,
	OutputArray _dst,
	int startPointX,
	int startPointY, 
	int detectSize,
	int detectNum,
	bool expressLine = FALSE);

#endif