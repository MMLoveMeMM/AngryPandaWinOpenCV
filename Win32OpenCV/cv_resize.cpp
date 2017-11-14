#include "stdafx.h"
#include "cv_resize.h"
#include <opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp> 
using namespace panda;
using namespace cv;

cv_resize::cv_resize()
{
}


cv_resize::~cv_resize()
{
}

int cv_resize::cvresize()
{
	Mat srcImage = imread("panda.jpg");  //工程目录下应该有一张名为1.jpg的素材图  
	Mat tmpImage, dstImage1, dstImage2;//临时变量和目标图的定义  
	tmpImage = srcImage;//将原始图赋给临时变量  

	//显示原始图    
	imshow("原始图", srcImage);

	//进行尺寸调整操作  
	/*
	* 最后一个参数 :
	* INTER_NEAREST - 最近邻插值
	* INTER_LINEAR - 线性插值（默认值）
	* INTER_AREA - 区域插值（利用像素区域关系的重采样插值）
	* INTER_CUBIC –三次样条插值（超过4×4像素邻域内的双三次插值）
	* INTER_LANCZOS4 -Lanczos插值（超过8×8像素邻域的Lanczos插值）
	*/
	resize(tmpImage, dstImage1, Size(tmpImage.cols / 2, tmpImage.rows / 2), (0, 0), (0, 0), 3);
	resize(tmpImage, dstImage2, Size(tmpImage.cols * 2, tmpImage.rows * 2), (0, 0), (0, 0), 3);

	//显示效果图    
	imshow("效果图 之一", dstImage1);
	imshow("效果图 之二", dstImage2);

	return 0;
}

int cv_resize::cvpyrup()
{
	Mat srcImage = imread("panda.jpg");  //工程目录下应该有一张名为1.jpg的素材图  
	Mat tmpImage, dstImage;//临时变量和目标图的定义  
	tmpImage = srcImage;//将原始图赋给临时变量  

	//显示原始图    
	imshow("【原始图】", srcImage);
	//进行向上取样操作  
	pyrUp(tmpImage, dstImage, Size(tmpImage.cols * 2, tmpImage.rows * 2));
	//显示效果图    
	imshow("【效果图】", dstImage);

	return 0;
}

int cv_resize::cvpydown()
{
	Mat srcImage = imread("panda.jpg");  //工程目录下应该有一张名为1.jpg的素材图  
	Mat tmpImage, dstImage;//临时变量和目标图的定义  
	tmpImage = srcImage;//将原始图赋给临时变量  

	//显示原始图    
	imshow("【原始图】", srcImage);
	//进行向下取样操作  
	pyrDown(tmpImage, dstImage, Size(tmpImage.cols / 2, tmpImage.rows / 2));
	//显示效果图    
	imshow("【效果图】", dstImage);

	return 0;
}
