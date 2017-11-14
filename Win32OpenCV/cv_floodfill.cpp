#include "stdafx.h"
#include "cv_floodfill.h"
#include <opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp>  
using namespace panda;
using namespace cv;

cv_floodfill::cv_floodfill()
{
}


cv_floodfill::~cv_floodfill()
{
}

int cv_floodfill::cvfloodfill()
{
	Mat src = imread("build.jpg");
	imshow("ԭʼͼ", src);
	Rect ccomp;
	floodFill(src, Point(50, 300), Scalar(155, 255, 55), &ccomp, Scalar(20, 20, 20), Scalar(20, 20, 20));
	imshow("Ч��ͼ", src);

	return 0;
}

/*
* API ����˵��:
floodFill : 
��һ��������InputOutputArray���͵�image, ����/���1ͨ����3ͨ����8λ�򸡵�ͼ�񣬾��������֮��Ĳ�������ָ����
�ڶ��������� InputOutputArray���͵�mask�����ǵڶ����汾��floodFill����Ĳ�������ʾ������ģ,����Ӧ��Ϊ��ͨ����8λ�����Ϳ��϶�������ͼ�� image ���������ص��ͼ�񡣵ڶ����汾��floodFill��Ҫʹ���Լ�������Ĥ���������mask��������һ��Ҫ����׼���ò����ڴ˴�����Ҫע����ǣ���ˮ��䲻�������Ĥmask�ķ��������������磬һ����Ե������ӵ��������������Ϊ��Ĥ���Է�ֹ��䵽��Ե��ͬ���ģ�Ҳ�����ڶ�εĺ���������ʹ��ͬһ����Ĥ���Ա�֤�������򲻻��ص���������Ҫע����ǣ���Ĥmask���������ͼ������� mask ��������ͼ��(x,y)���ص����Ӧ�ĵ������Ϊ(x+1,y+1)��
������������Point���͵�seedPoint����ˮ����㷨����ʼ�㡣
���ĸ�������Scalar���͵�newVal�����ص㱻Ⱦɫ��ֵ�������ػ��������ص���ֵ��
�����������Rect*���͵�rect����Ĭ��ֵ0��һ����ѡ�Ĳ�������������floodFill������Ҫ�ػ��������С�߽��������
������������Scalar���͵�loDiff����Ĭ��ֵScalar( )����ʾ��ǰ�۲�����ֵ���䲿����������ֵ���ߴ�����ò�������������֮������Ȼ���ɫ֮���lower brightness/color difference�������ֵ��
���߸�������Scalar���͵�upDiff����Ĭ��ֵScalar( )����ʾ��ǰ�۲�����ֵ���䲿����������ֵ���ߴ�����ò�������������֮������Ȼ���ɫ֮���lower brightness/color difference�������ֵ��
�ڰ˸�������int���͵�flags��������־�����˲��������������֣��Ƚϸ��ӣ�����һ����ϸ������
*/