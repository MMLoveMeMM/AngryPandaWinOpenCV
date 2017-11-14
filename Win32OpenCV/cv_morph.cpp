#include "stdafx.h"
#include "cv_morph.h"
#include <opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp> 
using namespace panda;
using namespace cv;

cv_morph::cv_morph()
{
}


cv_morph::~cv_morph()
{
}

int cv_morph::cvdilate()
{

	Mat image = imread("panda.jpg");

	namedWindow("膨胀操作 原图");
	namedWindow("膨胀操作 处理后");

	imshow("膨胀操作 原图", image);

	/*
	* 第一个参数 :
	*	矩形: MORPH_RECT
	*	交叉形: MORPH_CROSS
	*	椭圆形: MORPH_ELLIPSE
	* 第二个参数是卷积内核子
	*/
	Mat element = getStructuringElement(MORPH_RECT, Size(7, 7));
	Mat out;
	dilate(image, out, element);

	/*
	* 膨胀处理以后显示
	*/
	imshow("膨胀操作 效果图", out);

	return 0;
}

int cv_morph::cverode()
{
	Mat image = imread("panda.jpg");
 
	namedWindow("腐蚀操作 原图");
	namedWindow("腐蚀操作 效果图");

	imshow("腐蚀操作 原图", image);

	Mat element = getStructuringElement(MORPH_RECT, Size(15,15));
	Mat out;

	erode(image, out, element);

	imshow("腐蚀操作 效果图", out);

	return 0;
}

int cv_morph::cvmorphopen()
{
	Mat image = imread("panda.jpg"); 
	if (!image.data)
	{
		std::cout << "read image data failed !" << std::endl;
	}

	namedWindow("开运算 原图");
	namedWindow("开运算 效果图");

	imshow("开运算 原图", image);

	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//进行形态学操作  
	/*
	第三个参数设定如下:
	MORPH_OPEN – 开运算（Opening operation）
	MORPH_CLOSE – 闭运算（Closing operation）
	MORPH_GRADIENT -形态学梯度（Morphological gradient）
	MORPH_TOPHAT - “顶帽”（“Top hat”）
	MORPH_BLACKHAT - “黑帽”（“Black hat“）
	*/
	morphologyEx(image, image, MORPH_OPEN, element);

	imshow("开运算 效果图", image);

	return 0;
}

int cv_morph::cvmorphclose()
{
	Mat image = imread("panda.jpg");
	if (!image.data)
	{
		std::cout << "read image data failed !" << std::endl;
	}

	namedWindow("闭运算 原图");
	namedWindow("闭运算 效果图");

	imshow("闭运算 原图", image);

	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//进行形态学操作  
	/*
	第三个参数设定如下:
	MORPH_OPEN – 开运算（Opening operation）
	MORPH_CLOSE – 闭运算（Closing operation）
	MORPH_GRADIENT -形态学梯度（Morphological gradient）
	MORPH_TOPHAT - “顶帽”（“Top hat”）
	MORPH_BLACKHAT - “黑帽”（“Black hat“）
	*/
	morphologyEx(image, image, MORPH_CLOSE, element);

	imshow("闭运算 效果图", image);

	return 0;
}

int cv_morph::cvmorphgradient()
{
	Mat image = imread("panda.jpg");
	if (!image.data)
	{
		std::cout << "read image data failed !" << std::endl;
	}

	namedWindow("阶梯运算 原图");
	namedWindow("阶梯运算 效果图");

	imshow("阶梯运算 原图", image);

	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//进行形态学操作  
	/*
	第三个参数设定如下:
	MORPH_OPEN – 开运算（Opening operation）
	MORPH_CLOSE – 闭运算（Closing operation）
	MORPH_GRADIENT -形态学梯度（Morphological gradient）
	MORPH_TOPHAT - “顶帽”（“Top hat”）
	MORPH_BLACKHAT - “黑帽”（“Black hat“）
	*/
	morphologyEx(image, image, MORPH_GRADIENT, element);

	imshow("阶梯运算 效果图", image);

	return 0;
}
/*
* 其他的以此类推,只是调整那个参数
*/