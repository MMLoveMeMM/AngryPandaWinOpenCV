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
* ��ͼ
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
* ͼƬ�ں�
* ע�� : ͼƬ��СҪһ��
* �����ں�
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
* �ۺ�����Ĺ���
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
* API ˵��
*/
/*
void addWeighted(InputArray src1, double alpha, InputArray src2, double beta, double gamma, OutputArray
dst, int dtype=-1)

��һ��������InputArray���͵�src1����ʾ��Ҫ��Ȩ�ĵ�һ�����飬������һ��Mat��
�ڶ���������alpha����ʾ��һ�������Ȩ��
������������src2����ʾ�ڶ������飬����Ҫ�͵�һ������ӵ����ͬ�ĳߴ��ͨ������
���ĸ�������beta����ʾ�ڶ��������Ȩ��ֵ��
�����������dst����������飬�����������������ӵ����ͬ�ĳߴ��ͨ������
������������gamma��һ���ӵ�Ȩ���ܺ��ϵı���ֵ���������ʽ����Ȼ����⡣
���߸�������dtype��������еĿ�ѡ��ȣ���Ĭ��ֵ-1��;�������������������ͬ�����ʱ�������������Ϊ-1��Ĭ��ֵ��������ͬ��src1.depth����
��:
1�� ��1������������ͼƬ1��
2����2��������ͼƬ1���ںϱ��� : ����������Ե���
3����3������������ͼƬ2
4����4��������ͼƬ2���ںϱ��� : ����������Ե���
5����5��������ƫ��
6����6�����������ͼƬ
*/
