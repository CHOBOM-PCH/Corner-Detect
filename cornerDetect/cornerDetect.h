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

int cornerDetect(const char* route,//�ڳʸ� ã�Ƴ� �̹��� ��� //���� ã�� 1 �ƴ� -1
	int* distanceX,//�ڳʿ��� ī�޶��߽ɱ����� �Ÿ�
	int* distnaceY,
	int* pointX,//ã�Ƴ� �ڳ����� ��ġ
	int* pointY,
	int detectSize,//ã�Ե� ���� ������ �Ÿ�
	int detectNum,// ã�� ���� ����
	bool viewLine = FALSE);//���� ǥ�� ����

float cornerLineAngle(InputArray _edgeImage,//���� �˻��� edge �̹��� //ã�Ƴ� �ڳ������� �μ��� ����(degree:float)
	InputArray _src,// ���� �̹���
	OutputArray _dst,// ã�Ƴ� �� ������ ����� �̹���
	int startPointX,//�ڳ����� ����
	int startPointY,
	int detectSize,//ã�Ե� ���� ������ �Ÿ�
	int detectNum,// ã�� ���� ����
	bool viewLine = FALSE,//�ڳ������� ���۵� �� ���� ǥ�� ����(�⺻ ǥ�þ��� TRUE�� ǥ��)
	bool viewDetectPoint = FALSE);//�ڳ������� ���۵� ������ �ִ� ���� ǥ�� ����

#endif