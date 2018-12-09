#include "opencv2/opencv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
	
	Mat img(500,500, CV_8UC3);
	img.setTo(255);

	Point pt(300,300);
	line(img,Point(10,10),pt , CV_RGB(255,0,0),2);
	line(img,Point(300,10),Point(30,300) ,Scalar(255,0,0),2);
	//start , end , color , thickness
	
	circle(img, Point(250,250),100,CV_RGB(0,255,0),3);

	Point center(400,400);
	circle(img,center , 300 , Scalar(255,255,0),1);

	rectangle(img,Rect(10,10,200,200),CV_RGB(255,0,0),2);
	//x,y of left-top and width,height
	
	rectangle(img, Rect(Point(40,40),Point(400,400)), Scalar(255,0,0),2);	
	
	imshow("show",img);

		
	waitKey(0);
	return 0;

 
}
