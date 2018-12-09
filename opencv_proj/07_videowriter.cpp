#include "opencv2/opencv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
	
	VideoCapture capture(0);
	Mat frame;

	Size s = Size((int)capture.get(CV_CAP_PROP_FRAME_WIDTH),
	     (int)capture.get(CV_CAP_PROP_FRAME_HEIGHT));
	VideoWriter outVideo;
	outVideo.open("./outVideo.avi",0,capture.get(
				CV_CAP_PROP_FPS),s,1);
	
	// namedWindow("w");
	while(1){
		capture >> frame;
		outVideo << frame;
		// imshow("w",frame);
	}

		
	waitKey(0);
	return 0;

 
}
