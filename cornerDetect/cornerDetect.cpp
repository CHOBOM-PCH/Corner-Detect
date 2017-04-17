#include "cornerDetect.h"

using namespace cv;
using namespace std;

int cornerDetect(const char* route, int* distanceX, int* distanceY, int* pointX, int* pointY, int detectSize, int detectNum, bool viewLine)
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
	//imshow("img", edge_img);

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
	//cout << "cornerPoints.size() = " << cornerPoints.size() << endl;

	/*vector<Point>::const_iterator it;
	for (it = cornerPoints.begin(); it != cornerPoints.end(); ++it)	{
		circle(output_img, *it, 5, Scalar(0, 0, 255), 2);
		cout << "cornerPoints(" << (*it).x << ", " << (*it).y << ") " << endl;
	}*/


	//////////////////////코너 찾은 후 각도 측정////////////////
	vector<Point> confirmPoint;
	vector<float> confirmAngle;
	sLine* aLine = (0,0,0,0);
	sLine* bLine = (0,0,0,0);
	//float Angle = cornerLineAngle(edge_img, input_img, output_img, 377, 302, 15, 7);
	for (int i = 0; i < cornerPoints.size(); i++){
		float Angle = cornerLineAngle(edge_img, input_img, output_img, cornerPoints[i].x, cornerPoints[i].y, detectSize, detectNum);
		int x = cornerPoints[i].x;
		int y = cornerPoints[i].y;
		if (Angle > 80 && Angle < 100){
			confirmPoint.push_back(cornerPoints[i]);
			confirmAngle.push_back(Angle);
			/*cout<<">><<모서리 탐색 완료("<<x<<", "<<y<<", "<<Angle<<")"<<endl;
		}else if (Angle == 183) {
			cout<<"찾은게 2개이상 ("<<x<<", "<<y<<")"<<endl;
		}else if (Angle == 182) {
			cout<<"범위에서 벗어남 ("<<x<<", "<<y<<")"<<endl;
		}else if (Angle == 184) {
			cout<<"주변에선이 없음 ("<<x<<", "<<y<<")"<<endl;
		}else {
			cout<<"각도가 맞지 않음("<<x<<", "<<y<<", "<<Angle<<")"<<endl;*/
		}
	}
	for (int i = 0; i < confirmPoint.size(); i++){
		//cout<<" X: "<<confirmPoint[i].x<<" Y: "<<confirmPoint[i].y<<" Angle: "<<confirmAngle[i]<<"\n"<<endl;
		circle(output_img, Point(confirmPoint[i].x, confirmPoint[i].y),5, Scalar(0,0,255), 2);
	}
	if (confirmPoint.size() > 1){
		int j = 0;
		float d, a;
		for (int i = 0; i < confirmPoint.size(); i++){
			d = fabs(confirmAngle[i] - 90);
			if (i == 0){
				a = d;
				j = i;
			}else{
				if (a > d){
					a = d;
					j = i;
				}
			}
		}
		float conAngle = cornerLineAngle(edge_img, input_img, output_img, confirmPoint[j].x, confirmPoint[j].y, detectSize, detectNum, viewLine);
		//cout<<" X: "<<confirmPoint[j].x<<" Y: "<<confirmPoint[j].y<<" Angle: "<<conAngle<<"\n"<<endl;
		circle(output_img, Point(confirmPoint[j].x, confirmPoint[j].y),5, Scalar(0,255,0), 2);
		*pointX = confirmPoint[j].x;
		*pointY = confirmPoint[j].y;
		*distanceX = *pointX - (input_img.cols / 2);
		*distanceY = (input_img.rows / 2) - *pointY;
	}else if (confirmPoint.size() == 1) {
		cornerLineAngle(edge_img, input_img, output_img, confirmPoint[0].x, confirmPoint[0].y, detectSize, detectNum, viewLine);
		*pointX = confirmPoint[0].x;
		*pointY = confirmPoint[0].y;
		*distanceX = *pointX - (input_img.cols / 2);
		*distanceY = (input_img.rows / 2) - *pointY;
		//*distance = sqrt((double)(pow((double)(*pointY - (input_img.cols) / 2) , 2) 
		//	+ pow((double)(*pointX -  (input_img.rows) / 2) , 2))) ;
	}else {
		//cout << "찾는점이 없음"<<endl;
		return - 1;
	}

	////////////////////////////////////////////////////////
	circle(output_img, Point(input_img.cols / 2, input_img.rows / 2),5, Scalar(0,255,255), 2);
	line(output_img, Point(input_img.cols / 2, input_img.rows / 2), Point(*pointX, input_img.rows / 2),Scalar(255, 0, 0), 2);
	line(output_img, Point(*pointX, input_img.rows / 2), Point(*pointX, *pointY),Scalar(0, 0, 255), 2);

	//printf("edge값 : %d \n", data);

	imshow("output",output_img);
	


	return 1;
}
