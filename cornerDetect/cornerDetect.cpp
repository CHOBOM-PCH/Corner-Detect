#include "cornerDetect.h"

using namespace cv;
using namespace std;

int cornerDetect(const char* route, int* distance, int* pointX, int* pointY)
{
	
	Mat input_img = imread(route);
	Mat gray_img;
	Mat blur_img;
	Mat threshOutput_img;
	Mat edge_img;
	if (input_img.empty())
		return -1;
	Mat output_img;
	output_img = input_img.clone();
	Mat corner_img;
	cvtColor(input_img, gray_img, CV_BGR2GRAY);
	GaussianBlur(gray_img, blur_img, cv::Size(5,5), 30);
	//adaptiveThreshold(blur_img, threshOutput_img, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 15, 2);
	threshold(blur_img, threshOutput_img, 100, 255, THRESH_OTSU);
	Canny(threshOutput_img, edge_img, 100, 200);
	//imshow("input", input_img);
	//imshow("gray", gray_img);
	imshow("img", threshOutput_img);
	

	//cornerMinEigenVal(edge_img, corner_img, 2, 5);

	//Mat contour_img = threshOutput_img.clone();

	//vector<vector<Point> > contours;
	//findContours( contour_img, //외곽선 검출한후 저장
	//	contours, //외곽선 저장
	//	RETR_LIST, //모든 윤곽선 검색
	//	CHAIN_APPROX_SIMPLE);//양끝만 남김 제일위 제일아래 우측 좌측
	//const int cmin= 300;  // 최소 외곽선 길이
	//const int cmax= 500; // 최대 외곽선 길이
	//vector<vector<Point>>::const_iterator itc= contours.begin();
	//while (itc!=contours.end()) {//itc가 constours의 끝값이 아닌경우
	//	if (itc->size() < cmin || itc->size() > cmax)//itc의 크기(외곽선 크기)가 일정크기 제외삭제
	//		itc= contours.erase(itc);
	//	else 
	//		++itc;
	//}
	//drawContours(output_img,contours,-1,Scalar(0,255,0),2);
	////Rect bndRect = boundingRect(contours[0]);

	
	
	//float  eval;
	//for (int y = 0; y < corner_img.rows; y++)
	//for (int x = 0; x < corner_img.cols; x++)
	//{
	//	eval = corner_img.at<float>(y, x);

	//	if (eval > 0.2) // corner points
	//	{
	//		circle(output_img, Point(x, y), 5, Scalar(0, 0, 255), 2);
	//		//cout << "eval(" << x << ", " << y << ")= "
	//		//	<< eval << endl;
	//	}
	//}
	int maxCorners = 5;
	double qualityLevel = 0.001;
	double minDistance = 100;
	int    blockSize = 5;
	bool   useHarrisDetector = true;//false; // false
	double k = 0.04;

	vector<Point> cornerPoints;
	goodFeaturesToTrack(threshOutput_img, cornerPoints, maxCorners, qualityLevel,
		minDistance, noArray(), blockSize, useHarrisDetector, k);
	cout << "cornerPoints.size() = " << cornerPoints.size() << endl;
	
	vector<Point>::const_iterator it;
	for (it = cornerPoints.begin(); it != cornerPoints.end(); ++it)
	{
		circle(output_img, *it, 5, Scalar(0, 0, 255), 2);
		cout << "cornerPoints(" << (*it).x << ", " << (*it).y << ") " << endl;
	}

	imshow("output",output_img);
	*distance = 0;
	*pointX = 0;
	*pointY = 0;
		
	
	return 1;
}
