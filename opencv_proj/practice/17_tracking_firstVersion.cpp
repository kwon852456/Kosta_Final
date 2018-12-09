#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>


using namespace cv;
using namespace std;

void setLabel(Mat& image, string str, vector<Point> contour)
{
	int fontface = FONT_HERSHEY_SIMPLEX;
	double scale = 0.5;
	int thickness = 1;
	int baseline = 0;

	Size text = getTextSize(str, fontface, scale, thickness, &baseline);
	Rect r = boundingRect(contour);

	Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
	rectangle(image, pt + Point(0, baseline), pt + Point(text.width, -text.height), CV_RGB(200, 200, 200), CV_FILLED);
	putText(image, str, pt, fontface, scale, CV_RGB(0, 0, 0), thickness, 8);
}


int main(int argc , char** argv)
{
	int range_count = 0;

	Scalar red(0, 0, 255);
	Scalar blue(255, 0, 0);
	Scalar yellow(0, 255, 255);

	Scalar magenta(255, 0, 255);

	Scalar myColor(245,72,34);


	// Mat rgb_color = Mat(1, 1, CV_8UC3, red);
	Mat rgb_color = Mat(1, 1, CV_8UC3, red);
	Mat hsv_color;

	cvtColor(rgb_color, hsv_color, COLOR_BGR2HSV);


	int hue = (int)hsv_color.at<Vec3b>(0, 0)[0];
	int saturation = (int)hsv_color.at<Vec3b>(0, 0)[1];
	int value = (int)hsv_color.at<Vec3b>(0, 0)[2];



	cout << "hue = " << hue << endl;
	cout << "saturation = " << saturation << endl;
	cout << "value = " << value << endl;


	int low_hue = hue - 5;
	int high_hue = hue + 5;

	int low_hue1 = 0, low_hue2 = 0;
	int high_hue1 = 0, high_hue2 = 0;

	if (low_hue < 10 ) {
		range_count = 2;

		high_hue1 = 180;
		low_hue1 = low_hue + 180;
		high_hue2 = high_hue;
		low_hue2 = 0;
	}
	else if (high_hue > 170) {
		range_count = 2;

		high_hue1 = low_hue;
		low_hue1 = 180;
		high_hue2 = high_hue - 180;
		low_hue2 = 0;
	}
	else {
		range_count = 1;

		low_hue1 = low_hue;
		high_hue1 = high_hue;
	}


	cout << low_hue1 << "  " << high_hue1 << endl;
	cout << low_hue2 << "  " << high_hue2 << endl;

	// VideoCapture cap("rtspsrc location=rtsp://192.168.0.118:8554/test latency=0 ! rtph264depay ! decodebin ! videoconvert ! video/x-raw,width=400 , height=400 , format=(string)BGR ! appsink"
// );
	VideoCapture cap(0);

	Mat img_frame, img_hsv , img_result;


	if (!cap.isOpened()) {
		cerr << "ERROR! Unable to open camera\n";
		return -1;
	}


	for (;;)
	{
		// wait for a new frame from camera and store it into 'frame'
		cap.read(img_frame);

		// check if we succeeded
		if (img_frame.empty()) {
			cerr << "ERROR! blank frame grabbed\n";
			break;
		}


		//HSV로 변환
		cvtColor(img_frame, img_hsv, COLOR_BGR2HSV);


		//지정한 HSV 범위를 이용하여 영상을 이진화
		Mat img_mask1, img_mask2;
		inRange(img_hsv, Scalar(low_hue1, 50, 50), Scalar(high_hue1, 255, 255), img_mask1);
		if (range_count == 2) {
			inRange(img_hsv, Scalar(low_hue2, 50, 50), Scalar(high_hue2, 255, 255), img_mask2);
			img_mask1 |= img_mask2;
		}
		

		// morphological opening 작은 점들을 제거
		erode(img_mask1, img_mask1, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(img_mask1, img_mask1, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));


		// morphological closing 영역의 구멍 메우기
		dilate(img_mask1, img_mask1, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(img_mask1, img_mask1, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		// 라벨링
		Mat img_labels, stats, centroids;
		int numOfLables = connectedComponentsWithStats(img_mask1, img_labels,
			stats, centroids, 8, CV_32S);


		// 영역박스 그리기
		int max = -1, idx = 0;
		for (int j = 1; j < numOfLables; j++) {
			int area = stats.at<int>(j, CC_STAT_AREA);
			if (max < area && area > 700) 
			{
				max = area;
				idx = j;
			}
		}


		int left = stats.at<int>(idx, CC_STAT_LEFT);
		int top = stats.at<int>(idx, CC_STAT_TOP);
		int width = stats.at<int>(idx, CC_STAT_WIDTH);
		int height = stats.at<int>(idx, CC_STAT_HEIGHT);

		int x = centroids.at<double>(idx,0);
		int y = centroids.at<double>(idx,1);

		Rect r(left,top,width,height);


		rectangle(img_frame, Point(left, top), Point(left + width, top + height),
			Scalar(0, 0, 255), 1);

		cout << "x :" << x << endl;
		cout << "y :" << y << endl;

		imshow("rect", img_frame(r));
		Mat roi = img_mask1(r).clone();
		// cvtColor(roi,roi,CV_RGB2GRAY);
		/////////////////////도형 찾기 ///////////////
		
		//contour를 찾는다.
		vector<vector<Point> > contours;
		findContours(roi, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

		//contour를 근사화한다.
		vector<Point2f> approx;
		img_result = roi.clone();

		for (size_t i = 0; i < contours.size(); i++)
		{
			approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

			if (fabs(contourArea(Mat(approx))) > 100)  //면적이 일정크기 이상이어야 한다. 
			{

				int size = approx.size();

				//Contour를 근사화한 직선을 그린다.
				if (size % 2 == 0) {
					line(img_result, approx[0], approx[approx.size() - 1], Scalar(0, 255, 0), 3);

					for (int k = 0; k < size - 1; k++)
						line(img_result, approx[k], approx[k + 1], Scalar(0, 255, 0), 3);

					for (int k = 0; k < size; k++)
						circle(img_result, approx[k], 3, Scalar(0, 0, 255));
				}
				else {
					line(img_result, approx[0], approx[approx.size() - 1], Scalar(0, 255, 0), 3);

					for (int k = 0; k < size - 1; k++)
						line(img_result, approx[k], approx[k + 1], Scalar(0, 255, 0), 3);

					for (int k = 0; k < size; k++)
						circle(img_result, approx[k], 3, Scalar(0, 0, 255));
				}



				//도형을 판정한다.
				if (size == 3)
					setLabel(img_result, "triangle", contours[i]); //삼각형

				//이하는 해당 꼭지점을 가진 convex라면 찾는 도형
				else if (size == 4 && isContourConvex(Mat(approx))) 
					setLabel(img_result, "rectangle", contours[i]); //사각형

				else if (size == 5 && isContourConvex(Mat(approx))) 
					setLabel(img_result, "pentagon", contours[i]); //오각형

				else if (size == 6 && isContourConvex(Mat(approx))) 
					setLabel(img_result, "hexagon", contours[i]);  //육각형

				else if (size == 10 && isContourConvex(Mat(approx))) 
					setLabel(img_result, "decagon", contours[i]);    //십각형

				//위 조건에 해당 안되는 경우는 찾아낸 꼭지점 갯수를 표시
				else setLabel(img_result, to_string(approx.size()), contours[i]);
			}

		}
		
		
		///////////////////////////////////////////////

		namedWindow("binary video" , 0);
		namedWindow("origianl video" , 0);
		namedWindow("angle video" , 0);

		imshow("binary video", img_mask1);
		imshow("origianl video", img_frame);
		imshow("angle video", img_result);


		if (waitKey(5) >= 0)
			break;
	}


	return 0;
}
