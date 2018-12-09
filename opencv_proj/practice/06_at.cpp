#include "opencv2/opencv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
	
	Mat img = cv::imread("aaa.jpg");
	
	for (int i = 0 ; i < img.rows ; i++){
		for (int x = 0 ; x < img.cols ; x++){
			unsigned char b = img.at<Vec3b>(i,x)[0];
			unsigned char g = img.at<Vec3b>(i,x)[1];
			unsigned char r = img.at<Vec3b>(i,x)[2];

			img.at<Vec3b>(i,x)[0] = (unsigned char)(255-b);
			img.at<Vec3b>(i,x)[1] = (unsigned char)(255-g);
			img.at<Vec3b>(i,x)[2] = (unsigned char)(255-r);

		}
	}

	namedWindow("img",0);
	imshow("img",img);

		
	waitKey(0);
	return 0;

 
}
