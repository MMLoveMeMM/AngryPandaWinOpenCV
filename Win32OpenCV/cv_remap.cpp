#include "stdafx.h"
#include "cv_remap.h"
#include <opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp>  
using namespace panda;
using namespace cv;

cv_remap::cv_remap()
{
}


cv_remap::~cv_remap()
{
}

int cv_remap::cvremap()
{
	Mat srcImage, dstImage;
	Mat map_x, map_y;

	//【1】载入原始图  
	srcImage = imread("panda.jpg", 1);
	if (!srcImage.data) 
	{ 
		std::cout << "read image data failed !" << std::endl;
		return -1; 
	}
	imshow("原始图", srcImage);

	//【2】创建和原始图一样的效果图，x重映射图，y重映射图  
	dstImage.create(srcImage.size(), srcImage.type());
	map_x.create(srcImage.size(), CV_32FC1);
	map_y.create(srcImage.size(), CV_32FC1);

	//【3】双层循环，遍历每一个像素点，改变map_x & map_y的值  
	for (int j = 0; j < srcImage.rows; j++)
	{
		for (int i = 0; i < srcImage.cols; i++)
		{
			//改变map_x & map_y的值.   
			map_x.at<float>(j, i) = static_cast<float>(i);
			map_y.at<float>(j, i) = static_cast<float>(srcImage.rows - j);
		}
	}

	//【4】进行重映射操作  
	remap(srcImage, dstImage, map_x, map_y, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));

	//【5】显示效果图  
	imshow("效果图", dstImage);

	return 0;
}

/*
* API 函数说明:
* remap函数 :
* 第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可，且需为单通道8位或者浮点型图像。
第二个参数，OutputArray类型的dst，函数调用后的运算结果存在这里，即这个参数用于存放函数调用后的输出结果，需和源图片有一样的尺寸和类型。
第三个参数，InputArray类型的map1，它有两种可能的表示对象。
表示点（x，y）的第一个映射。
表示CV_16SC2 , CV_32FC1 或CV_32FC2类型的X值。
第四个参数，InputArray类型的map2，同样，它也有两种可能的表示对象，而且他是根据map1来确定表示那种对象。
若map1表示点（x，y）时。这个参数不代表任何值。
表示CV_16UC1 , CV_32FC1类型的Y值（第二个值）。
第五个参数，int类型的interpolation,插值方式，之前的resize( )函数中有讲到，需要注意，resize( )函数中提到的INTER_AREA插值方式在这里是不支持的，所以可选的插值方式如下：
INTER_NEAREST - 最近邻插值
INTER_LINEAR – 双线性插值（默认值）
INTER_CUBIC – 双三次样条插值（逾4×4像素邻域内的双三次插值）
INTER_LANCZOS4 -Lanczos插值（逾8×8像素邻域的Lanczos插值）

第六个参数，int类型的borderMode，边界模式，有默认值BORDER_CONSTANT，表示目标图像中“离群点（outliers）”的像素值不会被此函数修改。
第七个参数，const Scalar&类型的borderValue，当有常数边界时使用的值，其有默认值Scalar( )，即默认值为0。
*/