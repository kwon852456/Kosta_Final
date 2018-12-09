#include "opencv2/opencv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
	Mat img = imread("aaa.jpg");

	for (int i = img.rows/10 *5 ; i < img.rows / 10 *6 ; i++ ){
		
		Vec3b* ptr = img.ptr<Vec3b>(i);	
		for ( int x = 0 ; x < img.cols ; x++ ){
			
			unsigned char b1 = (ptr[x][0]);
			unsigned char g1 = (ptr[x][1]);
			unsigned char r1 = (ptr[x][2]);
				
			// Vec3b bgr = ptr[x];
			// unsigned char b2 = (ptr[x][0]);
			// unsigned char g2 = (ptr[x][1]);
			// unsigned char r2 = (ptr[x][2]);

			ptr[x] = Vec3b(255 - b1 , 255 - g1 , 255 - r1);
	 
		}
 
	}
	namedWindow("img" , 0);
	imshow("img",img);	

	waitKey(0);
	return 0;

 
}
