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
		cout<<"ã�Ƴ� ����Ʈ x: "<<x<<" y: "<<y<<"�߽ɿ��� �Ÿ�: X������ "
			<<distX<<"pixel Y������ "<<distY<<"pixel"<<endl;
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