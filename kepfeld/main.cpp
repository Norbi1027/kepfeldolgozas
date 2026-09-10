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

int main() {
	Mat img = imread("kep.jpg", IMREAD_UNCHANGED);

	//Mat fekete = Mat::zeros(img.size(), img.type());
	//Mat kep2(img.rows, img.cols, CV_8UC3); //pixelérték nem definiált
	//kep2.setTo(Scalar(0, 255,0));

	Mat img2;
	fakit2(img,img2);


	/*if (img.empty()) {
		cout << "nincs ott a kép" << endl;
		exit(-1);
	}

	Mat img2;
	//resize(img, img2, Size(200, 100));
	resize(img, img2, Size(img.cols / 2, img.rows / 2));

	int t = img.type();
	if (t == CV_8UC3) {
		cout << "szines (24bit)" << endl;
	}
	else {
		if (t == CV_8UC1) {
			cout << "szürkeskála (8 bit)" << endl;
		}
		else {
			cout << "egyeb" << endl;
		}
	}
	*/
	imshow("kep1", img);
	imshow("kep2", img2);
	//imshow("kep2", fekete);
	//imshow("kep3", kep2);
	waitKey();

	return 0;
}