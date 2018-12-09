#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"


using namespace cv;
using namespace std;

int main(){
	cout << " main () ...."<< endl;
   
     	Mat src = imread( "00.jpg", 0 );
     	Mat dst;
	Mat dst2;
	Mat dst3;

	namedWindow("source" , WINDOW_AUTOSIZE);
	namedWindow("result" , WINDOW_AUTOSIZE);

	// adaptiveThreshold(src,dst,255,cv::ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY||THRESH_OTSU,11,2);
	adaptiveThreshold(src,dst,255,cv::ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY||THRESH_OTSU,11,2);
	adaptiveThreshold(src,dst2,255,cv::ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY,11,2);
	threshold(src,dst3,0,255,THRESH_BINARY|THRESH_OTSU);
	//inputsrc,output,maxValue,Method,thresholdType,blockSize,constanValue to be minus from result	

 
     	imshow("source", src);
     	imshow("result", dst);  
     	imshow("result2", dst2);  
     	imshow("result3", dst3);  
             // imshow("result3", dst3);
 
     	waitKey(0);
     	return 0;
}
