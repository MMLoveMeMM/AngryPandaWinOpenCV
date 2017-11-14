#include "stdafx.h"
#include "cv_channels.h"
#include <opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp> 
#include <iostream>
#include<vector>
using namespace panda;
using namespace cv;
using namespace std;
cv_channels::cv_channels()
{
}

cv_channels::~cv_channels()
{
}

int cv_channels::multiChannelBlending()
{
	Mat srcImage;
	Mat maskImage;
	vector<Mat> channels;
	Mat imageBlueChannel;
	Mat imageRedChannel;
	Mat imageGreenChannel;
	
	maskImage = imread("Mantis.jpg", 0);
	srcImage = imread("panda.jpg");

	if (!maskImage.data || !srcImage.data)
	{
		std::cout << "read image failed!" << std::endl;
		return -1;
	}
	channels.resize(3);
	split(srcImage, channels);

	/*
	* 处理蓝色通道
	*/
	imageBlueChannel = channels.at(0);
	std::cout << "mask cols : " << maskImage.cols << " mask rows : " << maskImage.rows << std::endl;
	addWeighted(imageBlueChannel(Rect(350, 100, maskImage.cols, maskImage.rows)), 1.0,
		maskImage, 0.5, 0, imageBlueChannel(Rect(350, 100, maskImage.cols, maskImage.rows)));

	merge(channels, srcImage);

	namedWindow("blue channel");
	imshow("blue channel", srcImage);

	/*
	* 处理绿色通道
	*/
	imageGreenChannel = channels.at(1);
	std::cout << "mask cols : " << maskImage.cols << " mask rows : " << maskImage.rows << std::endl;
	addWeighted(imageGreenChannel(Rect(20, 25, maskImage.cols, maskImage.rows)), 1.0,
		maskImage, 0.5, 0, imageGreenChannel(Rect(20, 25, maskImage.cols, maskImage.rows)));

	merge(channels, srcImage);

	namedWindow("blue channel");
	imshow("blue channel", srcImage);

	/*
	* 处理红色通道
	*/
	imageGreenChannel = channels.at(2);
	std::cout << "mask cols : " << maskImage.cols << " mask rows : " << maskImage.rows << std::endl;
	addWeighted(imageGreenChannel(Rect(120, 25, maskImage.cols, maskImage.rows)), 1.0,
		maskImage, 0.5, 0, imageGreenChannel(Rect(120, 25, maskImage.cols, maskImage.rows)));

	merge(channels, srcImage);

	namedWindow("blue channel");
	imshow("blue channel", srcImage);

	return 0;
}

/*********************************************************************
* API 说明
*********************************************************************/
/*
void addWeighted(InputArray src1, double alpha, InputArray src2, double beta, double gamma, OutputArray
dst, int dtype=-1)

第一个参数，InputArray类型的src1，表示需要加权的第一个数组，常常填一个Mat。
第二个参数，alpha，表示第一个数组的权重
第三个参数，src2，表示第二个数组，它需要和第一个数组拥有相同的尺寸和通道数。
第四个参数，beta，表示第二个数组的权重值。
第五个参数，dst，输出的数组，它和输入的两个数组拥有相同的尺寸和通道数。
第六个参数，gamma，一个加到权重总和上的标量值。看下面的式子自然会理解。
第七个参数，dtype，输出阵列的可选深度，有默认值-1。;当两个输入数组具有相同的深度时，这个参数设置为-1（默认值），即等同于src1.depth（）
即:
1、 第1个参数，输入图片1，
2、第2个参数，图片1的融合比例 : 这个参数可以调节
3、第3个参数，输入图片2
4、第4个参数，图片2的融合比例 : 这个参数可以调节
5、第5个参数，偏差
6、第6个参数，输出图片
*/