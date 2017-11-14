#pragma once
#include<iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
namespace panda
{
class cv_brightness
{
public:
	cv_brightness();
	~cv_brightness();
public:
	static void on_trackbar(int, void*);
	static int createTrackbar(const std::string& threshold, const std::string& concom,int maxvalue);

	static void ContrastAndBright(int, void *);
	static int brignessTracker();
};
}


