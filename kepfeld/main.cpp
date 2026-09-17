#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/geometry.hpp>

using namespace std;
using namespace cv;

void fakit(Mat img) {
	img += 100;

}

void fakit2(const Mat img, Mat& dest) {
	dest = img + 100;
}

void invertal(const Mat img, Mat& dest) {
	if (img.channels() == 1) {
		dest = 255 - img;
	}
	else {
		dest = Scalar(255, 255, 255) - img;
	}
}

int main() {
	/*Mat fg = imread("kep.jpg", IMREAD_UNCHANGED);
	Mat bg = imread("background.jpg", IMREAD_UNCHANGED);


	if (fg.empty() || bg.empty()) {
		cout << "nincs ott a kép" << endl;
		exit(-1);
	}

	resize(bg, bg, fg.size());

	int value = 50;
	string winname = "eredmény";
	imshow(winname, fg);
	createTrackbar("alfa", winname, &value, 100);
	
	while (waitKey(1) != 'q') {
		double a = value / 100.0;
		Mat res = a * fg + (1 - a) * bg;
		imshow("eredmény", res);
	}
	*/



	/*Mat fg = imread("kep.jpg", IMREAD_UNCHANGED);

	if (fg.empty()) {
		cout << "nincs ott a kép" << endl;
		exit(-1);
	}

	int cut = 50;
	Rect r(	cut, 
			cut,
			fg.cols-2*cut,
			fg.rows-2*cut);
	Mat small = fg(r);
	imwrite("eredmeny.png", small);

	
	//waitKey();
	*/

	/*
	Mat fg (400,600,CV_8UC3);
	fg.setTo(Scalar(0, 0, 255));
	Rect r(0, 0, fg.cols, fg.rows / 2);
	fg(r).setTo(Scalar(0, 255, 255));

	Mat logo = imread("griff_black.png", IMREAD_UNCHANGED);
	resize(logo, logo, Size(300, 300));

	Rect r2(fg.cols / 2 - logo.cols / 2,
		fg.rows / 2 - logo.rows / 2,
		logo.cols,
		logo.rows);

	Mat mid = fg(r2);
	Mat mask = Scalar(255, 255, 255) - logo;


	//honnan.copyTo(hova)
	logo.copyTo(mid,mask);

	imshow("inv", mask);
	imshow("kozep", mid);
	imshow("kep1", fg);*/

	/*Mat fg = imread("background.jpg", IMREAD_COLOR);
	Mat kep = imread("kep.jpg", IMREAD_COLOR);
	resize(kep, kep, Size(200, 200));

	Rect r2(fg.cols / 2 = kep.cols / 2,
		fg.rows / 2 + 50,
		kep.cols,
		kep.rows);

	Mat mid = fg(r2);
	Mat mask = Scalar(255, 255, 255) - kep;

	kep.copyTo(mid, mask);

	imshow("inv", mask);
	imshow("kozep", mid);
	imshow("kep1", fg);

	*/

	Mat  kep = imread("kep.jpg", IMREAD_COLOR);
	Mat bg = imread("background.jpg", IMREAD_COLOR);
	resize(bg, bg, kep.size());

	Vec3b w(255, 255, 255);

	for (int i = 0; i < bg.rows; ++i) {
		for (int j = 0; j < bg.cols;++j) {
			if (kep.at<Vec3b>(i, j) != w) {
				bg.at<Vec3b>(i, j) = kep.at<Vec3b>(i, j);
			}
		}
	}

	//Mat fg = imread("background.jpg", IMREAD_COLOR);
	//cout << fg.at <Vec3b>(0, 0) << endl;
	//cout << fg.at <Vec3b>(fg.rows - 1, fg.cols - 1) << endl;

	//Mat fg2 = imread("background.jpg", IMREAD_COLOR);
	//cout << fg2.at <Vec3b>(0, 0) << endl;
	//cout << fg2.at <Vec3b>(fg2.rows - 1, fg2.cols - 1) << endl;

	imshow("kep1",bg);

	waitKey();


	return 0;
}