#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{


	Mat img = imread("00.jpg");

	Mat gray , binary , binary_th , binary_ad;
	cvtColor(img , gray , CV_RGB2GRAY);

	threshold(gray, binary_th , 128 , 255 , CV_THRESH_BINARY);
	cv::adaptiveThreshold(gray , binary_ad , 2244 , cv::ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY , 9 ,5);
	GaussianBlur(gray , gray , Size(7,7) , 0);
	threshold(gray , binary , 0 , 255 , CV_THRESH_BINARY+THRESH_OTSU);

	imshow("img" , img);
	imshow("otsu" ,binary);
	imshow("binary_ad" ,binary_ad);
	imshow("binary_th" ,binary_th);


	waitKey(0);

	return 0;
}
