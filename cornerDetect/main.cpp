#include "cornerDetect.h"

int main()
{
	const char* k = "image/5.jpg";
	int dist = 0;
	int x = 0;
	int y = 0;

	int detect = cornerDetect(k, &dist, &x, &y);
	if (detect == 1){
		cv::waitKey(0);
	}else if (detect = -1){
		printf("ã���� ����\n");
		cv::waitKey(0);
		system("pause");
	}else { 
		printf("point ����\n");
		cv::waitKey(0);
	}

}	