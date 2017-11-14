#include "stdafx.h"
#include "cv_cornerharris.h"
#include <opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp>  
using namespace panda;
using namespace cv;

cv_cornerharris::cv_cornerharris()
{
}


cv_cornerharris::~cv_cornerharris()
{
}

int cv_cornerharris::cvcornerHarris()
{
	Mat srcImage = imread("build.jpg", 0);
	imshow("ԭʼͼ", srcImage);

	//����Harris�ǵ����ҳ��ǵ�  
	Mat cornerStrength;
	cornerHarris(srcImage, cornerStrength, 2, 3, 0.01);

	//�ԻҶ�ͼ������ֵ�������õ���ֵͼ����ʾ    
	Mat harrisCorner;
	threshold(cornerStrength, harrisCorner, 0.00001, 255, THRESH_BINARY);
	imshow("�ǵ����Ķ�ֵЧ��ͼ", harrisCorner);

	return 0;
}

/*
* API ����:
cornerHarris����:
��һ��������InputArray���͵�src������ͼ�񣬼�Դͼ����Mat��Ķ��󼴿ɣ�����Ϊ��ͨ��8λ���߸�����ͼ��
�ڶ���������OutputArray���͵�dst���������ú���������������������������ڴ��Harris�ǵ��������������ԴͼƬ��һ���ĳߴ�����͡�
������������int���͵�blockSize����ʾ����Ĵ�С���������ϸ��Ϣ��cornerEigenValsAndVecs�������н�����
���ĸ�������int���͵�ksize����ʾSobel()���ӵĿ׾���С��
�����������double���͵�k��Harris������
������������int���͵�borderType��ͼ�����صı߽�ģʽ��ע������Ĭ��ֵBORDER_DEFAULT������ϸ�Ľ��ͣ��ο�borderInterpolate( )������

threshold���� :
��һ��������InputArray���͵�src���������飬�ͨ�� , 8��32λ�������͵�Mat���ɡ�
�ڶ���������OutputArray���͵�dst���������ú���������������������������ڴ�����������Һ͵�һ�������е�Mat������һ���ĳߴ�����͡�
������������double���͵�thresh����ֵ�ľ���ֵ��
���ĸ�������double���͵�maxval���������������ֵ����typeȡ CV_THRESH_BINARY ��CV_THRESH_BINARY_INV ��ֵ����ʱ�����ֵ.
�����������int���͵�type����ֵ����,��threshold( )����֧�ֵĶ�ͼ��ȡ��ֵ�ķ�������ȷ���������÷�����ͼ��

*/