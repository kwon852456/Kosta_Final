#include<iostream>
#include<opencv2/opencv.hpp>
#include<unistd.h>

using namespace std;
using namespace cv;

int main() {

	Mat image(200, 300, CV_8UC1, Scalar(255));
	namedWindow("Keyboard event", WINDOW_AUTOSIZE);
	imshow("Keyboard event", image);
	while (1) {
		int key = waitKey(1000);
		if (key == 27)
			break;
		else if (key == 255) {
			cout << "No keyboard event" << endl;
		}
		else if (char(key) == 'a'){
			cout << "a endtered" << endl;	
		}
		else {
			cout << "Entered : " << (char)key << endl;
		}
	}

	return 0;
}
