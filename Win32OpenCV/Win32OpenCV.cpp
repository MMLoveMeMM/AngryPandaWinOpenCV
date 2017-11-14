// Win32OpenCV.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include "opencv2/imgproc/imgproc.hpp"  
#include <iostream>  
#include "cv_sobel.h"
#include "cv_colors.h"
#include "cv_roi.h"
#include "cv_channels.h"
#include "cv_brightness.h"
#include "cv_blur.h"
#include "cv_filters.h"
#include "cv_morph.h"
#include "cv_canny.h"
#include "cv_resize.h"
#include "cv_hough.h"
#include "cv_floodfill.h"
#include "cv_cornerharris.h"
#include "cv_remap.h"
using namespace cv;
using namespace cv_;
using namespace panda;

int sobeltest()
{
	cv::Mat srcImage = cv::imread("panda.jpg", 0);
	if (!srcImage.data)
		return -1;
	cv::imshow("srcImage", srcImage);
	cv::Mat resultImage;
	// 非极大值抑制细化竖直sobel检测  
	cv_sobel::SobelVerEdge(srcImage, resultImage);
	cv::imshow("resultImage", resultImage);
	cv::Mat resultImage2;
	// 图像直接卷积实现sobel检测  
	cv_sobel::sobelEdge(srcImage, resultImage2, 100);
	cv::imshow("resultImage2", resultImage2);
	cv::Mat resultImage3;
	int flag = 2;
	// 图像卷积下非极大值抑制  
	//sobelOptaEdge(srcImage, resultImage3, 2);
	//cv::imshow("resultImage3", resultImage3);

	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	
	//cv_colors::cnvColor();

	//cv_roi::roiImage();
	//cv_roi::blendImage();
	//cv_roi::roilinearImage();

	//cv_channels::multiChannelBlending();

	//cv_brightness::createTrackbar("Threshold", "Connected Components",255);

	//cv_brightness::brignessTracker();

	//cv_blur::cvBoxBlur();
	//cv_blur::cvBlur();
	//cv_blur::cvGaussianBlur();
	//cv_filters::mediumfilter();
	//cv_filters::cvbilateralFilter();

	//cv_morph::cvdilate();
	//cv_morph::cverode();
	//cv_morph::cvmorphopen();
	//cv_morph::cvmorphclose();
	//cv_canny::cvcanny();
	//cv_sobel::cvsobel();
	//cv_sobel::cvlaplacian();

	//cv_sobel::cvscharr();

	//cv_resize::cvresize();
	//cv_resize::cvpyrup();

	//cv_hough::cvhoughlines();
	//cv_hough::cvhoughlinesp();
	//cv_hough::cvhoughcircles();

	//cv_floodfill::cvfloodfill();

	//cv_cornerharris::cvcornerHarris();

	cv_remap::cvremap();

	cv::waitKey(0);

	return 0;
}

