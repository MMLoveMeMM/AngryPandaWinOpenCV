#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp> 
#include "cv_filters.h"
using namespace panda;
using namespace cv;
/*
* 滤波器
*/
cv_filters::cv_filters()
{
}


cv_filters::~cv_filters()
{
}
/*
* 附近size的所有值中的一个处于中间的值[不大不小的那个值作为参考值]
*/
int cv_filters::mediumfilter()
{
	//载入原图  
	Mat image = imread("panda.jpg");

	//创建窗口  
	namedWindow("中值滤波【原图】");
	namedWindow("中值滤波【效果图】");

	//显示原图  
	imshow("中值滤波【原图】", image);

	//进行中值滤波操作  
	Mat out;
	medianBlur(image, out, 7);

	//显示效果图  
	imshow("中值滤波【效果图】", out);

	return 0;
}

int cv_filters::cvbilateralFilter()
{
	//载入原图  
	Mat image = imread("panda.jpg");

	//创建窗口  
	namedWindow("双边滤波【原图】");
	namedWindow("双边滤波【效果图】");

	//显示原图  
	imshow("双边滤波【原图】", image);

	//进行双边滤波操作  
	Mat out;
	bilateralFilter(image, out, 25, 25 * 2, 25 / 2);

	//显示效果图  
	imshow("双边滤波【效果图】", out);

	return 0;

}

/*
* API 函数
medianBlur
参数详解：
第一个参数，InputArray类型的src，函数的输入参数，填1、3或者4通道的Mat类型的图像；当ksize为3或者5的时候，图像深度需为CV_8U，CV_16U，或CV_32F其中之一，而对于较大孔径尺寸的图片，它只能是CV_8U。
第二个参数，OutputArray类型的dst，即目标图像，函数的输出参数，需要和源图片有一样的尺寸和类型。我们可以用Mat::Clone，以源图片为模板，来初始化得到如假包换的目标图。
第三个参数，int类型的ksize，孔径的线性尺寸（aperture linear size），注意这个参数必须是大于1的奇数，比如：3，5，7，9 ...
*/

/*
双边滤波原理:
http://blog.csdn.net/shenziheng1/article/details/50838970
*/
/*
bilateralFilter
第一个参数，InputArray类型的src，输入图像，即源图像，需要为8位或者浮点型单通道、三通道的图像。
第二个参数，OutputArray类型的dst，即目标图像，需要和源图片有一样的尺寸和类型。
第三个参数，int类型的d，表示在过滤过程中每个像素邻域的直径。如果这个值我们设其为非正数，那么OpenCV会从第五个参数sigmaSpace来计算出它来。
第四个参数，double类型的sigmaColor，颜色空间滤波器的sigma值。这个参数的值越大，就表明该像素邻域内有更宽广的颜色会被混合到一起，产生较大的半相等颜色区域。
第五个参数，double类型的sigmaSpace坐标空间中滤波器的sigma值，坐标空间的标注方差。他的数值越大，意味着越远的像素会相互影响，从而使更大的区域足够相似的颜色获取相同的颜色。当d>0，d指定了邻域大小且与sigmaSpace无关。否则，d正比于sigmaSpace。
第六个参数，int类型的borderType，用于推断图像外部像素的某种边界模式。注意它有默认值BORDER_DEFAULT。
*/