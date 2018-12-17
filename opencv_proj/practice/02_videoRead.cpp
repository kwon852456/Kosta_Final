#include "opencv2/opencv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
	VideoCapture capture("output.avi");
	Mat frame;

	//check
	if (!capture.isOpened()){
		printf("open failed");
		return 1;	
	
	}


	//create Window
	namedWindow("w");
	while(1){
		
		capture >> frame;

		if (frame.empty()){
			break;
		}	

		Sobel(frame , frame , frame.depth(),1,0);
		imshow("w",frame);
		if (waitKey(10) > 0)
			break;
	}
	
	waitKey(0);
	return 0;

 
}
