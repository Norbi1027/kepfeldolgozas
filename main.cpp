#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/geometry.hpp>
#include "histo.h"
#include "main.h"

using namespace std;
using namespace cv;
//6.ora?xd
void createHisto(const Mat img, Mat& hiszto) {
	//a hiszto az eredmeny, float típusú elemeket tartalmaz majd
	vector<Mat> kepek;
	kepek.push_back(img); // egy képet használunk
	vector<int> csatornak;
	csatornak.push_back(0); //a képnek a 0. csatornáját használjuk
	vector<int> hiszto_meretek;
	hiszto_meretek.push_back(256);  //szürkeárnyalatok száma
	vector<float> hiszto_tartomanyok;
	hiszto_tartomanyok.push_back(0.0f); //hol kezdődik a tartomány
	hiszto_tartomanyok.push_back(255.f);  //meddig tart
	//accumlate: marad false (nullázza a hisztogrammot)
	calcHist(kepek, csatornak, noArray(), hiszto, hiszto_meretek,
		hiszto_tartomanyok, false);
}


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

float differ(const Mat elab, const Mat lab) {
	Mat diff = elab - lab;
	Mat diff2 = diff.mul(diff);  // ez a mátrix szorzás
	vector<Mat> chs;
	split(diff2, chs); //dL^2 da^2 db^2
	Mat E;
	cv::sqrt(chs[0] + chs[1] + chs[2], E);
	return mean(E)[0];
}
//6.ora?
float find_th(const Mat img, float fg_ratio = 0.1f) {
	Mat histo;
	createHisto(img, histo);
	int n_pixels = img.cols * img.rows * fg_ratio;
	double d = 0;
	for (int i = 0; i < histo.rows * histo.cols; ++i) {
		d += histo.at<float>(i);
		if (d >= n_pixels) {
			return i;

		}
	}

}

void collectPoints(const Mat img,vector<Point>& pts){
	pts.clear();
	for (int i = 0; i < img.rows; i++){
		for (int j = 0; j < img.cols; j++){
			if (img.at<uchar>(i, j)) {
				pts.push_back(Point(j, i)); //!!!!!!!!!!!!!!!!
			}
		}
	}
}

void drawPoints(const Mat img, vector<Point>& pts,Mat& dest) {
	dest = img.clone();
	for (Point p:pts){
		drawMarker(dest, p, Scalar(0, 255, 0), MARKER_SQUARE, 10, 2);
	}
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

	/*
	Mat lab;
	Mat dest = imread("DEIK.jpg", IMREAD_COLOR);
	convert(dest, lab);
	Vec3f c1 = lab.at<Vec3f>(0, 0);
	Vec3f c2 = lab.at<Vec3f>(lab.rows - 1, 0);
	cout << c1 << " " << c2;
	cout << cv::norm(c1 - c2) << endl;

	*/


	// NEGYEEDIK ÓRA
	/*
		Mat elab, img, lab;
		Mat etalon = imread("etalon.png", IMREAD_COLOR);
		imshow("etalon", etalon);
		convert(etalon, elab);
		for (int i=0; i <=7;++i)
		{
			img = imread("fa_" + to_string(i) + ".png", IMREAD_COLOR);
			convert(img, lab);
			cout << differ(elab, lab) << endl;
			string wname = "fa_" + to_string(i);
			imshow(wname, img);
			moveWindow(wname, 500, 50 + i * (img.rows + 20));
		}

		*/
		/*
		Mat img = imread("orange1.jpg",IMREAD_COLOR);
		imshow("img", img);
		Histo::showHisto(img, "eredeti_histo", 1);

		vector<Mat> chs;
		Mat hsv;
		cvtColor(img, hsv, COLOR_BGR2HSV);
		split(hsv, chs);
		equalizeHist(chs[0], chs[0]);
		Mat res;
		merge(chs, res);
		cvtColor(res, res, COLOR_Lab2BGR);
		imshow("res", res);
		Histo::showHisto(res, "utana_histo", 1);

		*/
		/*
			VideoCapture cap("sas.avi");

			if (!cap.isOpened()) {
				cout << "nincs ott a fajl";
				exit(-1);
			}

			Mat img, gray, mask, dest;
			while (waitKey(25) != 'q') {
				cap >> img;
				if (img.empty()) {
					break;
				}
				cvtColor(img, gray, COLOR_BGR2GRAY);
				inRange(gray, 100, 155, mask);
				medianBlur(mask, mask, 5);
				dest = img.clone();
				dest.setTo(Scalar(0, 0, 0), mask);
				imshow("sas", dest);
			}
		*/

		//6.ora?
	/*
	Mat img = imread("scanned3.png", IMREAD_GRAYSCALE);
	Mat dest;
	int th = find_th(img);
	if (th == -1) {
		cout << "gatya" << endl;
	}
	else {
		threshold(img, dest, th, 255, THRESH_BINARY);
		imshow("dest", dest);
		waitKey();
	}

	*/

	/*
		Mat img = imread("zh.jpg", IMREAD_GRAYSCALE);
		imshow("img", img);
		int r = 1, c = 1;
		createTrackbar("sugar", "img", &r, 100);
		createTrackbar("r", "img", &c, 100);

		Mat dest;
		while (waitKey(1) != 'q') {
			int size = max(2 * r+1, 3);
			adaptiveThreshold(img, dest, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, size, c - 50);
			imshow("img",dest);
		}
		waitKey();
	*/

	/*
	Mat img = imread("csillagkod.jpg", IMREAD_GRAYSCALE);
	imshow("img", img);
	Mat mask;

	int r = 1;
	createTrackbar("s", "img", &r, 100);

	Mat dest;
	while (waitKey(1) != 'q') {
		int size = max(2 * r + 1, 3);

		Mat se = getStructuringElement(MORPH_RECT, Size(5, 5));
		morphologyEx(img, mask, MORPH_TOPHAT, se);
		imshow("mask", mask);
	}
	*/
	/*
		Mat img = imread("dog.jpg", IMREAD_GRAYSCALE);
		imshow("img", img);
		Mat mask;

		threshold(img, mask, 100, 255, THRESH_BINARY);
		imshow("mask", mask);

		int r = 1;
		createTrackbar("s", "img", &r, 100);

		Mat dest,dest2;
		while (waitKey(1) != 'q') {
			int size = max(2 * r + 1, 3);

			Mat se = getStructuringElement(MORPH_ELLIPSE, Size(size,size));
			erode(mask, dest, se);
			dilate(dest, dest2, se);
			imshow("erodalt", dest);
			imshow("visszadilatalt", dest2);
		}
	*/

	//7. ÓRA

/*
	Mat img = imread("szitakoto.jpg", IMREAD_GRAYSCALE);
	imshow("img", img);
	Mat mask;

	threshold(img, mask, 100, 255, THRESH_BINARY);

	int r = 1;
	createTrackbar("s", "img", &r, 100);

	Mat dest, dest2;
	while (waitKey(1) != 'q') {
		int size = max(2 * r + 1, 3);
		Mat mask2;
		Mat se = getStructuringElement(MORPH_ELLIPSE, Size(9, 9));

		erode(mask, dest, se, Point(-1, -1), 1, BORDER_CONSTANT, 0);
		//dilate(mask2, mask, se, Point(-1, -1), 1, BORDER_CONSTANT, 0);

		int x = mask.cols / 3;
		Rect r(x, 0, mask.cols - x - 1, mask.rows);

		cout << countNonZero(mask(r)) << endl;
		imshow("mask", mask(r));

	}

	*/



	Mat img = imread("annoltalt_sejt.png", IMREAD_COLOR);
	vector<Mat> chs;
	split(img, chs);
	Mat mask, dest;
	threshold(chs[2], mask, 250, 255, THRESH_BINARY);
	Mat mask2;
	Mat se = getStructuringElement(MORPH_CROSS, Size(3, 3));
	morphologyEx(mask, mask2, MORPH_HITMISS, se);
	vector<Point> pts;
	collectPoints(mask2, pts); //mask2 !!!!!!!!
	drawPoints(img, pts, dest);
	imshow("dest", dest);



	waitKey();
	return 0;
}

