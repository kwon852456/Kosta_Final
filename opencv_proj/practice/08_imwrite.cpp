#include "opencv2/opencv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
	
	Mat img = cv::imread("aaa.jpg");
	
	vector<Mat> rgbMat(3);
	split(img, rgbMat);

	imwrite("r.jpg", rgbMat[2]);
	imwrite("g.jpg", rgbMat[1]);
	imwrite("b.jpg", rgbMat[0]);


		
	waitKey(0);
	return 0;

 
}
