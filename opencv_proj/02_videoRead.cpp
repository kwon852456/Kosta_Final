#include "opencv2/opencv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
	const char* pipe = "-v rtspsrc location=rtsp://192.168.0.118:8554/test latency=0 ! rtph264depay ! decodebin ! videoconvert ! appsink";
	VideoCapture capture(pipe);
	Mat frame;

	//check
	if (!capture.isOpened()){
		printf("open failed");
		return 1;	
	
	}


	//create Window
	namedWindow("w");
	// namedWindow("w2",0);

	while(1){
		
		capture >> frame;

		if (frame.empty()){
			break;
		}	
		// Rect r(200,200,100,100);

		Sobel(frame , frame , frame.depth(),1,0);
		imshow("w",frame);
		// imshow("w2",frame(r));


		if (waitKey(10) > 0)
			break;
	}
	
	waitKey(0);
	return 0;

 
}
