#include "opencv2/opencv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
	
	Mat img = cv::imread("aaa.jpg");
	
	for (int i = 0 ; i < img.rows ; i++){
		for (int x = 0 ; x < img.cols ; x++){
			unsigned char r , g, b;
			b = img.data[i* img.step + x * img.elemSize() + 0];
			g = img.data[i* img.step + x * img.elemSize() + 1];
			r = img.data[i* img.step + x * img.elemSize() + 2];

			img.data[i* img.step + x * img.elemSize() + 0] = (unsigned char)(255-b);
			img.data[i* img.step + x * img.elemSize() + 1] = (unsigned char)(255-g);
			img.data[i* img.step + x * img.elemSize() + 2] = (unsigned char)(255-r);
		}
	}

	namedWindow("img",0);
	imshow("img",img);

		
	waitKey(0);
	return 0;

 
}
