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

	//定义点和向量  
	// vector<vector<Point>> contours;
	// vector<Vec4i> hierarchy;

	vector<Vec4i> hierarchy;
	vector<Mat> contours(10000);//手动分配内存空间大小
	findContours(bw, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);

	//查找轮廓  
	//findContours(bw, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	//初始化dst  
	Mat dst = Mat::zeros(img.size(), CV_8UC3);
	//开始处理  
	if (!contours.empty() && !hierarchy.empty())
	{
		//遍历所有顶层轮廓，随机生成颜色值绘制给各连接组成部分  
		int idx = 0;
		for (; idx >= 0; idx = hierarchy[idx][0])
		{
			Scalar color((rand() & 255), (rand() & 255), (rand() & 255));
			//绘制填充轮廓  
			drawContours(dst, contours, idx, color, CV_FILLED, 8, hierarchy);
		}
	}
	//显示窗口  
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

int g_nContrastValue; //对比度值  
int g_nBrightValue;  //亮度值  
Mat g_srcImage, g_dstImage;
void cv_brightness::ContrastAndBright(int, void *)
{

	//创建窗口  
	namedWindow("source image", 1);

	//三个for循环，执行运算 g_dstImage(i,j) =a*g_srcImage(i,j) + b  
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

	//显示图像  
	imshow("source image", g_srcImage);
	imshow("destination image", g_dstImage);
}
int cv_brightness::brignessTracker()
{
	//读入用户提供的图像  
	g_srcImage = imread("panda.jpg");
	if (!g_srcImage.data) { printf("Oh，no，读取g_srcImage图片错误~！\n"); return false; }
	g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());

	//设定对比度和亮度的初值  
	g_nContrastValue = 80;
	g_nBrightValue = 80;

	//创建窗口  
	namedWindow("destination image", 1);

	//创建轨迹条  
	cv::createTrackbar("对比度：", "destination", &g_nContrastValue, 300, ContrastAndBright);
	cv::createTrackbar("亮   度：", "destination", &g_nBrightValue, 200, ContrastAndBright);

	//调用回调函数  
	ContrastAndBright(g_nContrastValue, 0);
	ContrastAndBright(g_nBrightValue, 0);

	return 0;

}
/*********************************************************************
* API 说明
*********************************************************************/
/*
int createTrackbar(conststring& trackbarname, conststring& winname,
int* value, int count, TrackbarCallback onChange=0,void* userdata=0)
第一个参数，const string&类型的trackbarname，表示轨迹条的名字，用来代表我们创建的轨迹条。
第二个参数，const string&类型的winname，填窗口的名字，表示这个轨迹条会依附到哪个窗口上，即对应namedWindow（）创建窗口时填的某一个窗口名。
第三个参数，int* 类型的value，一个指向整型的指针，表示滑块的位置。并且在创建时，滑块的初始位置就是该变量当前的值。
第四个参数，int类型的count，表示滑块可以达到的最大位置的值。PS:滑块最小的位置的值始终为0。
第五个参数，TrackbarCallback类型的onChange，首先注意他有默认值0。这是一个指向回调函数的指针，每次滑块位置改变时，这个函数都会进行回调。并且这个函数的原型必须为void XXXX(int,void*);其中第一个参数是轨迹条的位置，第二个参数是用户数据（看下面的第六个参数）。如果回调是NULL指针，表示没有回调函数的调用，仅第三个参数value有变化。
第六个参数，void*类型的userdata，他也有默认值0。这个参数是用户传给回调函数的数据，用来处理轨迹条事件。如果使用的第三个参数value实参是全局变量的话，完全可以不去管这个userdata参数

*/