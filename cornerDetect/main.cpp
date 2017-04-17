#include "cornerDetect.h"

using namespace std;

int main()
{
	const char* k = "image/6.jpg";
	int distX = 0;
	int distY = 0;
	int x = 0;
	int y = 0;

	int detect = cornerDetect(k, &distX, &distY, &x, &y, 15, 7, TRUE);
	if (detect == 1){
		cout<<"찾아낸 포인트 x: "<<x<<" y: "<<y<<"중심에서 거리: X축으로 "
			<<distX<<"pixel Y축으로 "<<distY<<"pixel"<<endl;
		cv::waitKey(0);
	}else if (detect = -1){
		printf("찾을수 없음\n");
		cv::waitKey(0);
		system("pause");
	}else { 
		printf("point 많음\n");
		cv::waitKey(0);
	}

}	