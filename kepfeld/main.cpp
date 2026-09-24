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

void narancsmasolo(const Mat img, Mat& dest) {
	dest = Mat::zeros(img.size(), img.type());
	Mat mask, hsv;

	cvtColor(img, hsv, COLOR_BGR2HSV);
	Scalar ah(0, 0, 0);
	Scalar fh(30, 255, 255);
	inRange(hsv, ah, fh, mask);
	img.copyTo(dest, mask);
	imshow("mask", mask);
}

void tehenszinezo(const Mat img, Mat& dest)
{
	Mat hsv;

	cvtColor(img, hsv, COLOR_BGR2HSV);

	Mat_<Vec3b> hs = hsv;
	for (auto& p : hs) {
		if (p[0] > 130) {
			p[0] = 10;
			//p[1] -= 20; // kevésbé élénk
			p[2] -= 20; //sötét
		}
	}
	cvtColor(hs, dest, COLOR_HSV2BGR);
}

void mormotaMasolo(const Mat img, Mat& dest) {
	Mat hsv, mask;
	cvtColor(img, hsv, COLOR_BGR2HSV);
	//		   h  s  v
	Scalar ah(80, 0, 0);
	Scalar fh(160, 255, 255);
	inRange(hsv, ah, fh, mask);
	imshow("mask", 255 - mask);
	waitKey(0);

	Rect r(0, dest.rows - 1 - img.rows, img.cols, img.rows);
	img.copyTo(dest(r), 255 - mask);

}

void convert(const Mat img, Mat& lab) {
	Mat imgf;
	img.convertTo(imgf, CV_32FC3, 1 / 255.0);
	cvtColor(imgf, lab, COLOR_BGR2Lab);
}

	/*
	for (int i = 0; i < img.rows; ++i) {
		for (int j = 0; j < img.cols;++j) {
			Vec3b c = hsv.at<Vec3b>(i, j); //c[0] - h, c[1] - s, c[2] -v
			if (c[0] <30) {
				dest.at<Vec3b>(i, j) = img.at<Vec3b>(i,j);
			}
		}
	}
	*/

int main() {

	// MÁSODIK ÓRA

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

	*/

	//HARMADIK ÓRA
	
/*
	Mat_<Vec3b>  kep = imread("kep.jpg", IMREAD_COLOR);
	Mat_<Vec3b> bg = imread("background.jpg", IMREAD_COLOR);
	resize(bg, bg, kep.size());


	Vec3b w(255, 255, 255);

	for (int i = 0; i < bg.rows; ++i) {
		for (int j = 0; j < bg.cols;++j) {
			if (kep(i,j)[0] < 245 && kep(i,j)[1] <245) {
				bg(i,j) = kep(i,j);
			}
		}
	}

	vector<Mat> chs;
	split(kep, chs);
	imshow("R", chs[2]);
	imshow("G", chs[1]);
	imshow("B", chs[0]);
	imshow("kep1", bg);
	*/

	//Mat img = imread("orange1.jpg", IMREAD_COLOR);
	//Mat dest;
	//narancsmasolo(img, dest);
	//imshow("eredmeny", dest);

	/*
	Mat img = imread("milka.jpg", IMREAD_COLOR);
	Mat dest;
	tehenszinezo(img, dest);
	imshow("eredmeny", dest);
	*/

	/*
	Mat img = imread("mormota_kekhatter.jpg", IMREAD_COLOR);
	Mat dest = imread("Deik.jpg", IMREAD_COLOR);
	mormotaMasolo(img, dest);
	imshow("eredmeny", dest);
	*/

	Mat lab;
	Mat dest = imread("DEIK.jpg", IMREAD_COLOR);
	convert(dest, lab);
	Vec3f c1 = lab.at<Vec3f>(0, 0);
	Vec3f c2 = lab.at<Vec3f>(lab.rows - 1, 0);
	cout << c1 << " " << c2;
	cout << cv::norm(c1 - c2) << endl;


	waitKey();


	return 0;
}