#include "stdafx.h"
#include "cv_canny.h"
#include <opencv2/opencv.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include<opencv2/imgproc/imgproc.hpp>  
using namespace panda;
using namespace cv;

cv_canny::cv_canny()
{
}


cv_canny::~cv_canny()
{
}

int cv_canny::cvcanny()
{
	Mat src = imread("panda.jpg");  //工程目录下应该有一张名为1.jpg的素材图  
	if (!src.data)
	{
		std::cout << "read image failed \n" << std::endl;
		return -1;
	}
	Mat src1 = src.clone();

	//显示原始图   
	imshow("Canny边缘检测 原始图", src);

	//----------------------------------------------------------------------------------  
	//  一、最简单的canny用法，拿到原图后直接用。  
	//----------------------------------------------------------------------------------  
	Canny(src, src, 150, 100, 3);
	imshow("Canny边缘检测 效果图", src);

	Mat dst, edge, gray;

	// 【1】创建与src同类型和大小的矩阵(dst)  
	dst.create(src1.size(), src1.type());

	// 【2】将原图像转换为灰度图像  
	cvtColor(src1, gray, CV_BGR2GRAY);

	// 【3】先用使用 3x3内核来降噪  
	blur(gray, edge, Size(3, 3));

	// 【4】运行Canny算子  
	Canny(edge, edge, 3, 9, 3);

	//【5】将g_dstImage内的所有元素设置为0   
	dst = Scalar::all(0);

	//【6】使用Canny算子输出的边缘图g_cannyDetectedEdges作为掩码，来将原图g_srcImage拷到目标图g_dstImage中  
	src1.copyTo(dst, edge);

	//【7】显示效果图   
	imshow("anny边缘检测 效果图2", dst);

	return 0;
}

/*
* API函数:
Canny
第一个参数，InputArray类型的image，输入图像，即源图像，填Mat类的对象即可，且需为单通道8位图像。
第二个参数，OutputArray类型的edges，输出的边缘图，需要和源图片有一样的尺寸和类型。
第三个参数，double类型的threshold1，第一个滞后性阈值。
第四个参数，double类型的threshold2，第二个滞后性阈值。
第五个参数，int类型的apertureSize，表示应用Sobel算子的孔径大小，其有默认值3。
第六个参数，bool类型的L2gradient，一个计算图像梯度幅值的标识，有默认值false
*/
