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
	Canny(threshOutput_img, edge_img, 250, 300);
	//imshow("input", input_img);
	//imshow("gray", gray_img);
	//imshow("img", threshOutput_img);
	imshow("img", edge_img);
	
	//vector<Vec4i>lines;
	//HoughLinesP(edge_img, lines, 1, (PI / 180), 50, 50, 5);
	//
	//Vec4d params;//, avgparams;
	//
	//int x1, y1, x2, y2;
	//double angle = 0;
	//for (int k = 0; k < lines.size(); k++){
	//	params = lines[k];
	//	x1 = params[0];
	//	y1 = params[1];
	//	x2 = params[2];
	//	y2 = params[3];
	//	angle = abs(atan2f(((float)(y1 - y2)), abs((float)(x2 - x1))) * 180 / PI);
	//	Point pt1(x1, y1),pt2(x2, y2);
	//	line(output_img, pt1, pt2, Scalar(255, 0, 255), 1);
	//	printf("시작점 %d, %d  끝점 %d %d  각도 %lf \n", x1, y1, x2, y2, angle);
	//}


	int maxCorners = 20;
	double qualityLevel = 0.001;
	double minDistance = 10;
	int    blockSize = 5;
	bool   useHarrisDetector = true;//false; // false
	double k = 0.04;

	vector<Point> cornerPoints;
	goodFeaturesToTrack(threshOutput_img, cornerPoints, maxCorners, qualityLevel,
		minDistance, noArray(), blockSize, useHarrisDetector, k);
	cout << "cornerPoints.size() = " << cornerPoints.size() << endl;
	
	vector<Point>::const_iterator it;
	for (it = cornerPoints.begin(); it != cornerPoints.end(); ++it)	{
		circle(output_img, *it, 5, Scalar(0, 0, 255), 2);
		cout << "cornerPoints(" << (*it).x << ", " << (*it).y << ") " << endl;
	}
	
	
	//for (it = cornerPoints.begin(); it != cornerPoints.end(); ++it) {
	int z = 0;
	int d = 0;
	vector<Vec2i>detectPoint;
	
	//double dx, dy;
	//sPoint *aDirection = new sPoint[10];
	//sPoint *bDirection = new sPoint[10];
	int dx, dy;
	sPointi *aDirection = new sPointi[10];
	sPointi *bDirection = new sPointi[10];
	if (z == 0) {
		aDirection[z].x = 158;
		aDirection[z].y = 190;
		bDirection[z].x = 158;
		bDirection[z].y = 190;
		dx = aDirection[z].x + 10;
		for (dy = aDirection[z].y - 10; dy <= aDirection[z].y + 10; dy++) {
			int whiteDetect = edge_img.at<uchar>(dy,dx);
			if (whiteDetect == 255){
				detectPoint[d][0] = dx;
				detectPoint[d][1] = dy;
				d++;
			}
		}
		dx = aDirection[z].x - 10;
		for (dy = aDirection[z].y - 10; dy <= aDirection[z].y + 10; dy++) {
			int whiteDetect = edge_img.at<uchar>(dy,dx);
			if (whiteDetect == 255){
				detectPoint[d][0] = dx;
				detectPoint[d][1] = dy;
				d++;
			}
		}
		dy = aDirection[z].y + 10;
		for (dx = aDirection[z].x - 10; dx <= aDirection[z].x + 10; dx++) {
			int whiteDetect = edge_img.at<uchar>(dy,dx);
			if (whiteDetect == 255){
				//detectPoint[d][0] = dx;
				//detectPoint[d][1] = dy;
				detectPoint.push_back()= (dx, dy);
				d++;
			}
		}
		dy = aDirection[z].y - 10;
		for (dx = aDirection[z].x - 10; dx <= aDirection[z].x + 10; dx++) {
			int whiteDetect = edge_img.at<uchar>(dy,dx);
			if (whiteDetect == 255){
				detectPoint[d][0] = dx;
				detectPoint[d][1] = dy;
				d++;
			}
		}
		printf ("point 크기 %d \n", d);
		z++;
	}//else if (z != 10){

	//}
	


	int data = edge_img.at<uchar>(189,157);//(y,x)

	printf("edge값 : %d \n", data);

	imshow("output",output_img);
	*distance = 0;
	*pointX = 0;
	*pointY = 0;
		
	
	return 1;
}
