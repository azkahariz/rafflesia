#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core.hpp>
#include <opencv2/video.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>
#include <math.h>
#ifndef VARIABEL
#define VARIABEL

using namespace std;
using namespace cv;

// Background Substraction
Ptr<BackgroundSubtractor> pBackSub;
Mat frame, fgMask, fgMask2;

Mat dilatasi;

vector<vector<Point> > contours;
vector<Vec4i> hierarchy;

// Berfungsi untuk mencuplik frame pada video real-time
Mat src;

// Membuat varibael titik korespondensi
Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");
std::vector<DMatch> matches;

// Variabel cuplik video
VideoCapture cap;

// Variabel untuk menampilkan titik korespondensi
Mat imMatches;

// Varibale untuk gambar referensi
Mat imReference;

// Registered image will be resotred in imReg.
// The estimated homography will be stored in h.
Mat imReg, h;

// Untuk mencari homography
std::vector<Point2f> points1, points2;

Mat img;
// Koordinat
std::vector<Point2d> titik, titik2;

Mat imRegGray;
stringstream ss;
string JarakText, degreeText;
int jarakX, jarakY, radius;
double jarak, degree;
vector<Vec3f> circlesTarget, circlesBomb;

Mat element = getStructuringElement(MORPH_ELLIPSE, Size(3,3));

#endif // VARIABEL
