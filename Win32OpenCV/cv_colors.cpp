#include "stdafx.h"
#include "cv_colors.h"
#include <opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
using namespace panda;

cv_colors::cv_colors()
{
}


cv_colors::~cv_colors()
{
}

int cv_colors::cnvColor()
{
	// Load image
	cv::Mat srcImage = cv::imread("panda.jpg"), dstImage;

	// Convert to other color space
	cv::cvtColor(srcImage, dstImage, cv::COLOR_BGR2Lab);
	imshow("Lab Space", dstImage);

	cv::cvtColor(srcImage, dstImage, cv::COLOR_BGR2GRAY);
	imshow("Gray Scale", dstImage);

	return 0;
}
