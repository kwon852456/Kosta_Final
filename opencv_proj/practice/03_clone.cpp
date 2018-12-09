#include "opencv2/opencv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
	Mat img = imread("aaa.jpg");

	//clone #1
	Mat img2 = img.clone();

	cv::bitwise_not(img , img2);
	// 색 반전
	namedWindow("img" , 0);
	namedWindow("img2" , 0);
	imshow("img", img);
	imshow("img2" , img2);

	Rect r(img2.cols / 4 , img2.rows /4 , img2.cols / 4 * 2 , img2.rows / 4 * 2);
	// 세로 1/4 지점 가로 1/4 지점에 세로 파일 크기 반 가로 파일크기 반 네모
	cout << r << endl;

	//clone #2
	Mat img3 = img2(r).clone();
	//copy only boundary of r
	imshow("img3" , img3);	
	
	//clone #3
	Mat img4;
	img(r).copyTo(img4);
	imshow("img4" , img4);

	//clone #4  영상 두개 가로로 합치기
	Mat img5(Size(img.cols * 2 , img.rows) , img.type());
	img5.setTo(255);

	img.copyTo(img5(Range::all() , Range(0,img.cols)));
	img2.copyTo(img5(Range::all() , Range(img2.cols , img2.cols *2)));

	namedWindow("img5" , 0);
	imshow("img5" , img5);
	
	//clone #5 일정영역만 복사 주소만을 가져오기 때문에 원본에 영향을 준다..!
	Mat roi(img, r);
	bitwise_not(roi , roi);
	imshow("roi" , roi);
	imshow("img" , img);	
	
	
	waitKey(0);
	return 0;

 
}
