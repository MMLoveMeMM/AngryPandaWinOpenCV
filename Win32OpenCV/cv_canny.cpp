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
	Mat src = imread("panda.jpg");  //����Ŀ¼��Ӧ����һ����Ϊ1.jpg���ز�ͼ  
	if (!src.data)
	{
		std::cout << "read image failed \n" << std::endl;
		return -1;
	}
	Mat src1 = src.clone();

	//��ʾԭʼͼ   
	imshow("Canny��Ե��� ԭʼͼ", src);

	//----------------------------------------------------------------------------------  
	//  һ����򵥵�canny�÷����õ�ԭͼ��ֱ���á�  
	//----------------------------------------------------------------------------------  
	Canny(src, src, 150, 100, 3);
	imshow("Canny��Ե��� Ч��ͼ", src);

	Mat dst, edge, gray;

	// ��1��������srcͬ���ͺʹ�С�ľ���(dst)  
	dst.create(src1.size(), src1.type());

	// ��2����ԭͼ��ת��Ϊ�Ҷ�ͼ��  
	cvtColor(src1, gray, CV_BGR2GRAY);

	// ��3������ʹ�� 3x3�ں�������  
	blur(gray, edge, Size(3, 3));

	// ��4������Canny����  
	Canny(edge, edge, 3, 9, 3);

	//��5����g_dstImage�ڵ�����Ԫ������Ϊ0   
	dst = Scalar::all(0);

	//��6��ʹ��Canny��������ı�Եͼg_cannyDetectedEdges��Ϊ���룬����ԭͼg_srcImage����Ŀ��ͼg_dstImage��  
	src1.copyTo(dst, edge);

	//��7����ʾЧ��ͼ   
	imshow("anny��Ե��� Ч��ͼ2", dst);

	return 0;
}

/*
* API����:
Canny
��һ��������InputArray���͵�image������ͼ�񣬼�Դͼ����Mat��Ķ��󼴿ɣ�����Ϊ��ͨ��8λͼ��
�ڶ���������OutputArray���͵�edges������ı�Եͼ����Ҫ��ԴͼƬ��һ���ĳߴ�����͡�
������������double���͵�threshold1����һ���ͺ�����ֵ��
���ĸ�������double���͵�threshold2���ڶ����ͺ�����ֵ��
�����������int���͵�apertureSize����ʾӦ��Sobel���ӵĿ׾���С������Ĭ��ֵ3��
������������bool���͵�L2gradient��һ������ͼ���ݶȷ�ֵ�ı�ʶ����Ĭ��ֵfalse
*/
