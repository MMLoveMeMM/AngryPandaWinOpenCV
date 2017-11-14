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
	* ������ɫͨ��
	*/
	imageBlueChannel = channels.at(0);
	std::cout << "mask cols : " << maskImage.cols << " mask rows : " << maskImage.rows << std::endl;
	addWeighted(imageBlueChannel(Rect(350, 100, maskImage.cols, maskImage.rows)), 1.0,
		maskImage, 0.5, 0, imageBlueChannel(Rect(350, 100, maskImage.cols, maskImage.rows)));

	merge(channels, srcImage);

	namedWindow("blue channel");
	imshow("blue channel", srcImage);

	/*
	* ������ɫͨ��
	*/
	imageGreenChannel = channels.at(1);
	std::cout << "mask cols : " << maskImage.cols << " mask rows : " << maskImage.rows << std::endl;
	addWeighted(imageGreenChannel(Rect(20, 25, maskImage.cols, maskImage.rows)), 1.0,
		maskImage, 0.5, 0, imageGreenChannel(Rect(20, 25, maskImage.cols, maskImage.rows)));

	merge(channels, srcImage);

	namedWindow("blue channel");
	imshow("blue channel", srcImage);

	/*
	* �����ɫͨ��
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
* API ˵��
*********************************************************************/
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