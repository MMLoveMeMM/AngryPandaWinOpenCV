#include "stdafx.h"
#include "cv_roi.h"
#include <opencv2/opencv.hpp>
using namespace panda;
using namespace cv;
cv_roi::cv_roi()
{
}


cv_roi::~cv_roi()
{
}
/*
* 贴图
*/
int cv_roi::roiImage()
{
	Mat srcImage1 = imread("panda.jpg");
	Mat maskImage = imread("mask.jpg");
	if (!maskImage.data)
	{
		std::cout << "read mask.png error !" << std::endl;
		return -1;
	}

	Mat imageRoi = srcImage1(Rect(200, 250, maskImage.cols, maskImage.rows));

	Mat mask = imread("mask.jpg", 0);
	maskImage.copyTo(imageRoi, mask);

	namedWindow("roi test");
	imshow("roi test",srcImage1);

	return 0;
}

/*
* 图片融合
* 注意 : 图片大小要一致
* 线性融合
*/
int cv_roi::blendImage()
{
	double alphaValue = 0.5;
	double betaValue;
	Mat srcImage2, srcImage3, dstImage;

	srcImage2 = imread("Crane.jpg");
	srcImage3 = imread("Mantis.jpg");

	if (!srcImage2.data || !srcImage3.data)
	{
		std::cout << "read data failed !" << std::endl;
		return -1;
	}

	betaValue = (1.0 - alphaValue);
	addWeighted(srcImage2, alphaValue, srcImage3, betaValue, 0.0, dstImage);

	namedWindow("src image", 1);
	imshow("src image",srcImage2);

	namedWindow("dst image", 1);
	imshow("dst image", dstImage);

	return 0;
}
/*
* 综合上面的功能
*/
int cv_roi::roilinearImage()
{
	Mat srcImage4 = imread("panda.jpg", 1);
	Mat maskImage = imread("mask.jpg");

	Mat imageRoi;
	imageRoi = srcImage4(Rect(250, 250, maskImage.cols, maskImage.rows));

	addWeighted(imageRoi, 0.5, maskImage, 0.3, 0.0, imageRoi);

	namedWindow("roi linear image");
	imshow("roi linear image", srcImage4);

	return 0;

}

/*
* API 说明
*/
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
