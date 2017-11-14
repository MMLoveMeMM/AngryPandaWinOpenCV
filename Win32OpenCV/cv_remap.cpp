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

	//��1������ԭʼͼ  
	srcImage = imread("panda.jpg", 1);
	if (!srcImage.data) 
	{ 
		std::cout << "read image data failed !" << std::endl;
		return -1; 
	}
	imshow("ԭʼͼ", srcImage);

	//��2��������ԭʼͼһ����Ч��ͼ��x��ӳ��ͼ��y��ӳ��ͼ  
	dstImage.create(srcImage.size(), srcImage.type());
	map_x.create(srcImage.size(), CV_32FC1);
	map_y.create(srcImage.size(), CV_32FC1);

	//��3��˫��ѭ��������ÿһ�����ص㣬�ı�map_x & map_y��ֵ  
	for (int j = 0; j < srcImage.rows; j++)
	{
		for (int i = 0; i < srcImage.cols; i++)
		{
			//�ı�map_x & map_y��ֵ.   
			map_x.at<float>(j, i) = static_cast<float>(i);
			map_y.at<float>(j, i) = static_cast<float>(srcImage.rows - j);
		}
	}

	//��4��������ӳ�����  
	remap(srcImage, dstImage, map_x, map_y, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));

	//��5����ʾЧ��ͼ  
	imshow("Ч��ͼ", dstImage);

	return 0;
}

/*
* API ����˵��:
* remap���� :
* ��һ��������InputArray���͵�src������ͼ�񣬼�Դͼ����Mat��Ķ��󼴿ɣ�����Ϊ��ͨ��8λ���߸�����ͼ��
�ڶ���������OutputArray���͵�dst���������ú���������������������������ڴ�ź������ú�������������ԴͼƬ��һ���ĳߴ�����͡�
������������InputArray���͵�map1���������ֿ��ܵı�ʾ����
��ʾ�㣨x��y���ĵ�һ��ӳ�䡣
��ʾCV_16SC2 , CV_32FC1 ��CV_32FC2���͵�Xֵ��
���ĸ�������InputArray���͵�map2��ͬ������Ҳ�����ֿ��ܵı�ʾ���󣬶������Ǹ���map1��ȷ����ʾ���ֶ���
��map1��ʾ�㣨x��y��ʱ����������������κ�ֵ��
��ʾCV_16UC1 , CV_32FC1���͵�Yֵ���ڶ���ֵ����
�����������int���͵�interpolation,��ֵ��ʽ��֮ǰ��resize( )�������н�������Ҫע�⣬resize( )�������ᵽ��INTER_AREA��ֵ��ʽ�������ǲ�֧�ֵģ����Կ�ѡ�Ĳ�ֵ��ʽ���£�
INTER_NEAREST - ����ڲ�ֵ
INTER_LINEAR �C ˫���Բ�ֵ��Ĭ��ֵ��
INTER_CUBIC �C ˫����������ֵ����4��4���������ڵ�˫���β�ֵ��
INTER_LANCZOS4 -Lanczos��ֵ����8��8���������Lanczos��ֵ��

������������int���͵�borderMode���߽�ģʽ����Ĭ��ֵBORDER_CONSTANT����ʾĿ��ͼ���С���Ⱥ�㣨outliers����������ֵ���ᱻ�˺����޸ġ�
���߸�������const Scalar&���͵�borderValue�����г����߽�ʱʹ�õ�ֵ������Ĭ��ֵScalar( )����Ĭ��ֵΪ0��
*/