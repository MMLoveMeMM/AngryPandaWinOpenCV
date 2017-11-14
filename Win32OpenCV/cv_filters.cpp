#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp> 
#include "cv_filters.h"
using namespace panda;
using namespace cv;
/*
* �˲���
*/
cv_filters::cv_filters()
{
}


cv_filters::~cv_filters()
{
}
/*
* ����size������ֵ�е�һ�������м��ֵ[����С���Ǹ�ֵ��Ϊ�ο�ֵ]
*/
int cv_filters::mediumfilter()
{
	//����ԭͼ  
	Mat image = imread("panda.jpg");

	//��������  
	namedWindow("��ֵ�˲���ԭͼ��");
	namedWindow("��ֵ�˲���Ч��ͼ��");

	//��ʾԭͼ  
	imshow("��ֵ�˲���ԭͼ��", image);

	//������ֵ�˲�����  
	Mat out;
	medianBlur(image, out, 7);

	//��ʾЧ��ͼ  
	imshow("��ֵ�˲���Ч��ͼ��", out);

	return 0;
}

int cv_filters::cvbilateralFilter()
{
	//����ԭͼ  
	Mat image = imread("panda.jpg");

	//��������  
	namedWindow("˫���˲���ԭͼ��");
	namedWindow("˫���˲���Ч��ͼ��");

	//��ʾԭͼ  
	imshow("˫���˲���ԭͼ��", image);

	//����˫���˲�����  
	Mat out;
	bilateralFilter(image, out, 25, 25 * 2, 25 / 2);

	//��ʾЧ��ͼ  
	imshow("˫���˲���Ч��ͼ��", out);

	return 0;

}

/*
* API ����
medianBlur
������⣺
��һ��������InputArray���͵�src�������������������1��3����4ͨ����Mat���͵�ͼ�񣻵�ksizeΪ3����5��ʱ��ͼ�������ΪCV_8U��CV_16U����CV_32F����֮һ�������ڽϴ�׾��ߴ��ͼƬ����ֻ����CV_8U��
�ڶ���������OutputArray���͵�dst����Ŀ��ͼ�񣬺����������������Ҫ��ԴͼƬ��һ���ĳߴ�����͡����ǿ�����Mat::Clone����ԴͼƬΪģ�壬����ʼ���õ���ٰ�����Ŀ��ͼ��
������������int���͵�ksize���׾������Գߴ磨aperture linear size����ע��������������Ǵ���1�����������磺3��5��7��9 ...
*/

/*
˫���˲�ԭ��:
http://blog.csdn.net/shenziheng1/article/details/50838970
*/
/*
bilateralFilter
��һ��������InputArray���͵�src������ͼ�񣬼�Դͼ����ҪΪ8λ���߸����͵�ͨ������ͨ����ͼ��
�ڶ���������OutputArray���͵�dst����Ŀ��ͼ����Ҫ��ԴͼƬ��һ���ĳߴ�����͡�
������������int���͵�d����ʾ�ڹ��˹�����ÿ�����������ֱ����������ֵ��������Ϊ����������ôOpenCV��ӵ��������sigmaSpace�������������
���ĸ�������double���͵�sigmaColor����ɫ�ռ��˲�����sigmaֵ�����������ֵԽ�󣬾ͱ����������������и�������ɫ�ᱻ��ϵ�һ�𣬲����ϴ�İ������ɫ����
�����������double���͵�sigmaSpace����ռ����˲�����sigmaֵ������ռ�ı�ע���������ֵԽ����ζ��ԽԶ�����ػ��໥Ӱ�죬�Ӷ�ʹ����������㹻���Ƶ���ɫ��ȡ��ͬ����ɫ����d>0��dָ���������С����sigmaSpace�޹ء�����d������sigmaSpace��
������������int���͵�borderType�������ƶ�ͼ���ⲿ���ص�ĳ�ֱ߽�ģʽ��ע������Ĭ��ֵBORDER_DEFAULT��
*/