#include "opencv2/opencv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
	
	namedWindow("show1",0);
	// namedWindow("threshold",0);
	// namedWindow("contours",0);

	Mat img;
	img = imread("aaa.jpg");

	cvtColor(img,img,CV_RGB2GRAY);

	threshold(img,img , 128 , 255, CV_THRESH_BINARY);

	Mat dst = Mat::zeros(img.rows,img.cols,CV_8UC3);

	vector <vector<Point>> contours;
	vector <Vec4i> hierarchy;

	findContours(img.clone(),contours , hierarchy,
		RETR_CCOMP, CHAIN_APPROX_SIMPLE);

	//ex 1)
	drawContours(dst , contours , -1 , CV_RGB(255,0,0) ,1,8,hierarchy);	


	imshow("show1",dst);
		
	waitKey(0);
	return 0;

 
}
