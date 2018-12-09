#include "opencv2/opencv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
	
	Mat img = cv::imread("00.jpg");
	//imread("ss.jpg",0); -> garayscale
	namedWindow("img" , 0 );
	imshow("img" , img);


	waitKey(0);
	return 0;

 
}
