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


	int maxCorners = 100;
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
	

	//////////////////////코너 찾은 후 각도 측정////////////////
	vector<Point> confirmPoint;
	sLine* aLine = (0,0,0,0);
	sLine* bLine = (0,0,0,0);
	for (int i = 0; i < cornerPoints.size(); i++){
		float Angle = cornerLineAngle(edge_img, input_img, output_img, cornerPoints[i].x, cornerPoints[i].y, 10, 5);
		int x = cornerPoints[i].x;
		int y = cornerPoints[i].y;
		if (Angle < 100 && Angle > 80){
			confirmPoint.push_back(cornerPoints[i]);
			cout<<"cornerAngle "<<Angle<<endl;
		}else if (Angle == 183) {
			cout<<"찾은게 2개이상 ("<<x<<", "<<y<<")"<<endl;
		}else if (Angle == 182) {
			cout<<"범위에서 벗어남 ("<<x<<", "<<y<<")"<<endl;
		}else if (Angle == 184) {
			cout<<"주변에선이 없음 ("<<x<<", "<<y<<")"<<endl;
		}
	}
	for (int i = 0; i < confirmPoint.size(); i++){
		cout<<" X: "<<confirmPoint[i].x<<" Y: "<<confirmPoint[i].y<<"\n"<<endl;
		circle(output_img, Point(confirmPoint[i].x, confirmPoint[i].y),5, Scalar(0,0,255), 2);
	}
	////////////////////////////////////////////////////////
	//circle(output_img, Point(166, 179),5, Scalar(0,0,255), 2);
	//int data = edge_img.at<uchar>(75,294);//(y,x)

	//printf("edge값 : %d \n", data);

	imshow("output",output_img);
	*distance = 0;
	*pointX = 0;
	*pointY = 0;


	return 1;
}
