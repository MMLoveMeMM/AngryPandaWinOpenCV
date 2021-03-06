#include "stdafx.h"
#include "cv_hough.h"
#include <opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp>  
using namespace panda;
using namespace cv;

cv_hough::cv_hough()
{
}


cv_hough::~cv_hough()
{
}
/*
* http://blog.csdn.net/tina_ttl/article/details/53063341
*/
int cv_hough::cvhoughlines()
{
	Mat srcImage = imread("build.jpg");  //工程目录下应该有一张名为1.jpg的素材图  
	Mat midImage, dstImage;//临时变量和目标图的定义  

	//【2】进行边缘检测和转化为灰度图  
	Canny(srcImage, midImage, 50, 200, 3);//进行一此canny边缘检测  
	cvtColor(midImage, dstImage, CV_GRAY2BGR);//转化边缘检测后的图为灰度图  

	//【3】进行霍夫线变换  
	std::vector<Vec2f> lines;//定义一个矢量结构lines用于存放得到的线段矢量集合  
	HoughLines(midImage, lines, 1, CV_PI / 180, 150, 0, 0);

	//【4】依次在图中绘制出每条线段  
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, CV_AA);
	}

	//【5】显示原始图    
	imshow("【原始图】", srcImage);

	//【6】边缘检测后的图   
	imshow("【边缘检测后的图】", midImage);

	//【7】显示效果图    
	imshow("【效果图】", dstImage);

	return 0;
}

int cv_hough::cvhoughlinesp()
{

	Mat srcImage = imread("build.jpg");  //工程目录下应该有一张名为1.jpg的素材图  
	Mat midImage, dstImage;//临时变量和目标图的定义  

	//【2】进行边缘检测和转化为灰度图  
	Canny(srcImage, midImage, 50, 200, 3);//进行一此canny边缘检测  
	cvtColor(midImage, dstImage, CV_GRAY2BGR);//转化边缘检测后的图为灰度图  

	//【3】进行霍夫线变换  
	std::vector<Vec4i> lines;//定义一个矢量结构lines用于存放得到的线段矢量集合  
	HoughLinesP(midImage, lines, 1, CV_PI / 180, 80, 50, 10);

	//【4】依次在图中绘制出每条线段  
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255), 1, CV_AA);
	}

	//【5】显示原始图    
	imshow("【原始图】", srcImage);

	//【6】边缘检测后的图   
	imshow("【边缘检测后的图】", midImage);

	//【7】显示效果图    
	imshow("【效果图】", dstImage);

	return 0;
}

int cv_hough::cvhoughcircles()
{
	Mat srcImage = imread("yuan.jpg");  //工程目录下应该有一张名为1.jpg的素材图  
	Mat midImage, dstImage;//临时变量和目标图的定义  

	//【2】显示原始图  
	imshow("【原始图】", srcImage);

	//【3】转为灰度图，进行图像平滑  
	cvtColor(srcImage, midImage, CV_BGR2GRAY);//转化边缘检测后的图为灰度图  
	GaussianBlur(midImage, midImage, Size(9, 9), 2, 2);

	//【4】进行霍夫圆变换  
	std::vector<Vec3f> circles;
	HoughCircles(midImage, circles, CV_HOUGH_GRADIENT, 1.5, 10, 200, 100, 0, 0);

	//【5】依次在图中绘制出圆  
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		//绘制圆心  
		circle(srcImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		//绘制圆轮廓  
		circle(srcImage, center, radius, Scalar(155, 50, 255), 3, 8, 0);
	}

	//【6】显示效果图    
	imshow("【效果图】", srcImage);
	return 0;
}