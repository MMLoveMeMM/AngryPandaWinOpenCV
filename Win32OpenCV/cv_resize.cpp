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
	Mat srcImage = imread("panda.jpg");  //����Ŀ¼��Ӧ����һ����Ϊ1.jpg���ز�ͼ  
	Mat tmpImage, dstImage1, dstImage2;//��ʱ������Ŀ��ͼ�Ķ���  
	tmpImage = srcImage;//��ԭʼͼ������ʱ����  

	//��ʾԭʼͼ    
	imshow("ԭʼͼ", srcImage);

	//���гߴ��������  
	/*
	* ���һ������ :
	* INTER_NEAREST - ����ڲ�ֵ
	* INTER_LINEAR - ���Բ�ֵ��Ĭ��ֵ��
	* INTER_AREA - �����ֵ���������������ϵ���ز�����ֵ��
	* INTER_CUBIC �C����������ֵ������4��4���������ڵ�˫���β�ֵ��
	* INTER_LANCZOS4 -Lanczos��ֵ������8��8���������Lanczos��ֵ��
	*/
	resize(tmpImage, dstImage1, Size(tmpImage.cols / 2, tmpImage.rows / 2), (0, 0), (0, 0), 3);
	resize(tmpImage, dstImage2, Size(tmpImage.cols * 2, tmpImage.rows * 2), (0, 0), (0, 0), 3);

	//��ʾЧ��ͼ    
	imshow("Ч��ͼ ֮һ", dstImage1);
	imshow("Ч��ͼ ֮��", dstImage2);

	return 0;
}

int cv_resize::cvpyrup()
{
	Mat srcImage = imread("panda.jpg");  //����Ŀ¼��Ӧ����һ����Ϊ1.jpg���ز�ͼ  
	Mat tmpImage, dstImage;//��ʱ������Ŀ��ͼ�Ķ���  
	tmpImage = srcImage;//��ԭʼͼ������ʱ����  

	//��ʾԭʼͼ    
	imshow("��ԭʼͼ��", srcImage);
	//��������ȡ������  
	pyrUp(tmpImage, dstImage, Size(tmpImage.cols * 2, tmpImage.rows * 2));
	//��ʾЧ��ͼ    
	imshow("��Ч��ͼ��", dstImage);

	return 0;
}

int cv_resize::cvpydown()
{
	Mat srcImage = imread("panda.jpg");  //����Ŀ¼��Ӧ����һ����Ϊ1.jpg���ز�ͼ  
	Mat tmpImage, dstImage;//��ʱ������Ŀ��ͼ�Ķ���  
	tmpImage = srcImage;//��ԭʼͼ������ʱ����  

	//��ʾԭʼͼ    
	imshow("��ԭʼͼ��", srcImage);
	//��������ȡ������  
	pyrDown(tmpImage, dstImage, Size(tmpImage.cols / 2, tmpImage.rows / 2));
	//��ʾЧ��ͼ    
	imshow("��Ч��ͼ��", dstImage);

	return 0;
}
