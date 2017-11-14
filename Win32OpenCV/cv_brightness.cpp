#include "stdafx.h"
#include "cv_brightness.h"
using namespace panda;
using namespace cv;
static Mat img;
static int threshval = 160;

cv_brightness::cv_brightness()
{
}


cv_brightness::~cv_brightness()
{
}

void cv_brightness::on_trackbar(int, void*)
{
	Mat bw = threshval < 128 ? (img < threshval) : (img > threshval);

	//����������  
	// vector<vector<Point>> contours;
	// vector<Vec4i> hierarchy;

	vector<Vec4i> hierarchy;
	vector<Mat> contours(10000);//�ֶ������ڴ�ռ��С
	findContours(bw, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);

	//��������  
	//findContours(bw, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	//��ʼ��dst  
	Mat dst = Mat::zeros(img.size(), CV_8UC3);
	//��ʼ����  
	if (!contours.empty() && !hierarchy.empty())
	{
		//�������ж������������������ɫֵ���Ƹ���������ɲ���  
		int idx = 0;
		for (; idx >= 0; idx = hierarchy[idx][0])
		{
			Scalar color((rand() & 255), (rand() & 255), (rand() & 255));
			//�����������  
			drawContours(dst, contours, idx, color, CV_FILLED, 8, hierarchy);
		}
	}
	//��ʾ����  
	imshow("Connected Components", dst);
}

int cv_brightness::createTrackbar(const std::string& threshold, const std::string& concom, int maxvalue)
{
	img = imread("panda.jpg");
	if (!img.data)
	{
		std::cout << "fail read image datas !" << std::endl;
		return -1;
	}

	namedWindow("image", 1);
	imshow("image", img);

	namedWindow("concom", 1);
	//cv::createTrackbar(threshold, concom, &threshval, maxvalue,on_trackbar);
	cv::createTrackbar("Threshold", "Connected Components", &threshval, 255, on_trackbar);
	on_trackbar(threshval, 0);

	return 0;

}

int g_nContrastValue; //�Աȶ�ֵ  
int g_nBrightValue;  //����ֵ  
Mat g_srcImage, g_dstImage;
void cv_brightness::ContrastAndBright(int, void *)
{

	//��������  
	namedWindow("source image", 1);

	//����forѭ����ִ������ g_dstImage(i,j) =a*g_srcImage(i,j) + b  
	for (int y = 0; y < g_srcImage.rows; y++)
	{
		for (int x = 0; x < g_srcImage.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				g_dstImage.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((g_nContrastValue*0.01)*(g_srcImage.at<Vec3b>(y, x)[c]) + g_nBrightValue);
			}
		}
	}

	//��ʾͼ��  
	imshow("source image", g_srcImage);
	imshow("destination image", g_dstImage);
}
int cv_brightness::brignessTracker()
{
	//�����û��ṩ��ͼ��  
	g_srcImage = imread("panda.jpg");
	if (!g_srcImage.data) { printf("Oh��no����ȡg_srcImageͼƬ����~��\n"); return false; }
	g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());

	//�趨�ԱȶȺ����ȵĳ�ֵ  
	g_nContrastValue = 80;
	g_nBrightValue = 80;

	//��������  
	namedWindow("destination image", 1);

	//�����켣��  
	cv::createTrackbar("�Աȶȣ�", "destination", &g_nContrastValue, 300, ContrastAndBright);
	cv::createTrackbar("��   �ȣ�", "destination", &g_nBrightValue, 200, ContrastAndBright);

	//���ûص�����  
	ContrastAndBright(g_nContrastValue, 0);
	ContrastAndBright(g_nBrightValue, 0);

	return 0;

}
/*********************************************************************
* API ˵��
*********************************************************************/
/*
int createTrackbar(conststring& trackbarname, conststring& winname,
int* value, int count, TrackbarCallback onChange=0,void* userdata=0)
��һ��������const string&���͵�trackbarname����ʾ�켣�������֣������������Ǵ����Ĺ켣����
�ڶ���������const string&���͵�winname����ڵ����֣���ʾ����켣�����������ĸ������ϣ�����ӦnamedWindow������������ʱ���ĳһ����������
������������int* ���͵�value��һ��ָ�����͵�ָ�룬��ʾ�����λ�á������ڴ���ʱ������ĳ�ʼλ�þ��Ǹñ�����ǰ��ֵ��
���ĸ�������int���͵�count����ʾ������Դﵽ�����λ�õ�ֵ��PS:������С��λ�õ�ֵʼ��Ϊ0��
�����������TrackbarCallback���͵�onChange������ע������Ĭ��ֵ0������һ��ָ��ص�������ָ�룬ÿ�λ���λ�øı�ʱ���������������лص����������������ԭ�ͱ���Ϊvoid XXXX(int,void*);���е�һ�������ǹ켣����λ�ã��ڶ����������û����ݣ�������ĵ�����������������ص���NULLָ�룬��ʾû�лص������ĵ��ã�������������value�б仯��
������������void*���͵�userdata����Ҳ��Ĭ��ֵ0������������û������ص����������ݣ���������켣���¼������ʹ�õĵ���������valueʵ����ȫ�ֱ����Ļ�����ȫ���Բ�ȥ�����userdata����

*/