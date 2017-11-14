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

	namedWindow("���Ͳ��� ԭͼ");
	namedWindow("���Ͳ��� �����");

	imshow("���Ͳ��� ԭͼ", image);

	/*
	* ��һ������ :
	*	����: MORPH_RECT
	*	������: MORPH_CROSS
	*	��Բ��: MORPH_ELLIPSE
	* �ڶ��������Ǿ���ں���
	*/
	Mat element = getStructuringElement(MORPH_RECT, Size(7, 7));
	Mat out;
	dilate(image, out, element);

	/*
	* ���ʹ����Ժ���ʾ
	*/
	imshow("���Ͳ��� Ч��ͼ", out);

	return 0;
}

int cv_morph::cverode()
{
	Mat image = imread("panda.jpg");
 
	namedWindow("��ʴ���� ԭͼ");
	namedWindow("��ʴ���� Ч��ͼ");

	imshow("��ʴ���� ԭͼ", image);

	Mat element = getStructuringElement(MORPH_RECT, Size(15,15));
	Mat out;

	erode(image, out, element);

	imshow("��ʴ���� Ч��ͼ", out);

	return 0;
}

int cv_morph::cvmorphopen()
{
	Mat image = imread("panda.jpg"); 
	if (!image.data)
	{
		std::cout << "read image data failed !" << std::endl;
	}

	namedWindow("������ ԭͼ");
	namedWindow("������ Ч��ͼ");

	imshow("������ ԭͼ", image);

	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//������̬ѧ����  
	/*
	�����������趨����:
	MORPH_OPEN �C �����㣨Opening operation��
	MORPH_CLOSE �C �����㣨Closing operation��
	MORPH_GRADIENT -��̬ѧ�ݶȣ�Morphological gradient��
	MORPH_TOPHAT - ����ñ������Top hat����
	MORPH_BLACKHAT - ����ñ������Black hat����
	*/
	morphologyEx(image, image, MORPH_OPEN, element);

	imshow("������ Ч��ͼ", image);

	return 0;
}

int cv_morph::cvmorphclose()
{
	Mat image = imread("panda.jpg");
	if (!image.data)
	{
		std::cout << "read image data failed !" << std::endl;
	}

	namedWindow("������ ԭͼ");
	namedWindow("������ Ч��ͼ");

	imshow("������ ԭͼ", image);

	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//������̬ѧ����  
	/*
	�����������趨����:
	MORPH_OPEN �C �����㣨Opening operation��
	MORPH_CLOSE �C �����㣨Closing operation��
	MORPH_GRADIENT -��̬ѧ�ݶȣ�Morphological gradient��
	MORPH_TOPHAT - ����ñ������Top hat����
	MORPH_BLACKHAT - ����ñ������Black hat����
	*/
	morphologyEx(image, image, MORPH_CLOSE, element);

	imshow("������ Ч��ͼ", image);

	return 0;
}

int cv_morph::cvmorphgradient()
{
	Mat image = imread("panda.jpg");
	if (!image.data)
	{
		std::cout << "read image data failed !" << std::endl;
	}

	namedWindow("�������� ԭͼ");
	namedWindow("�������� Ч��ͼ");

	imshow("�������� ԭͼ", image);

	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//������̬ѧ����  
	/*
	�����������趨����:
	MORPH_OPEN �C �����㣨Opening operation��
	MORPH_CLOSE �C �����㣨Closing operation��
	MORPH_GRADIENT -��̬ѧ�ݶȣ�Morphological gradient��
	MORPH_TOPHAT - ����ñ������Top hat����
	MORPH_BLACKHAT - ����ñ������Black hat����
	*/
	morphologyEx(image, image, MORPH_GRADIENT, element);

	imshow("�������� Ч��ͼ", image);

	return 0;
}
/*
* �������Դ�����,ֻ�ǵ����Ǹ�����
*/