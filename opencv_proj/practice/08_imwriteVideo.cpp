#include <opencv2/opencv.hpp>
#include <iostream>  
#include "opencv2/opencv.hpp"  
#include <cstdlib>
#include <cstring>
 
using namespace cv;
using namespace std;
 
 
int main(){
	const char* pipe = "-v rtspsrc location=rtsp://192.168.0.131:8554/test latency=0 ! rtph264depay ! decodebin ! videoconvert ! appsink";

	VideoCapture capture(pipe);
	Mat frame;

	int askFileTypeBox = 0;
	int Color = 1;
	Size S = Size((int)capture.get(CV_CAP_PROP_FRAME_WIDTH), 
			(int)capture.get(CV_CAP_PROP_FRAME_HEIGHT));

	VideoWriter outVideo;
	outVideo.open("outvideo.avi" ,askFileTypeBox , capture.get(CV_CAP_PROP_FPS), S ,Color);

	if(!capture.isOpened())
		return 0;

	namedWindow("w");

	int x = 0;
	string path = "./images/";
	string number = to_string(x);
	string s = ".jpg";
	string name = path+number+s;

	while(1){
		capture >> frame;
		if(frame.empty())
			break;	

		
		outVideo.write(frame);
		number = to_string(x);
		name = path+number+s;
		x++;
		imwrite(name , frame);
		imshow("w",frame);
		if(waitKey(10) > 0)
			break;
	}
    return 0;
}
