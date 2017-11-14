#include "stdafx.h"
#include "cv_blur.h"
#include <opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp> 
using namespace panda;
using namespace cv;
cv_blur::cv_blur()
{
}


cv_blur::~cv_blur()
{
}

int cv_blur::cvBoxBlur()
{
	//载入原图  
	Mat image = imread("panda.jpg");
	if (!image.data)
	{
		std::cout << "failed to read image !" << std::endl;
		return -1;
	}
	//创建窗口  
	namedWindow("方框滤波【原图】");
	namedWindow("方框滤波【效果图】");

	//显示原图  
	imshow("方框滤波【原图】", image);

	//进行滤波操作  
	Mat out;
	/*
	* 方框滤波
	*/
	boxFilter(image, out, -1, Size(5, 5));//最后一个参数非常重要,也是该算法的核心所在,表征内核算子,调节这个改变模糊程度

	//显示效果图  
	imshow("方框滤波【效果图】", out);

	return 0;
}

int cv_blur::cvBlur()
{
	//载入原图  
	Mat image = imread("panda.jpg");
	if (!image.data)
	{
		std::cout << "failed to read image !" << std::endl;
		return -1;
	}

	//创建窗口  
	namedWindow("均值滤波【原图】");
	namedWindow("均值滤波【效果图】");

	//显示原图  
	imshow("均值滤波【原图】", image);

	//进行均值滤波操作  
	Mat out;
	blur(image, out, Size(7, 7));//最后一个参数非常重要,也是该算法的核心所在,表征内核算子,调节这个改变模糊程度

	//显示效果图  
	imshow("均值滤波【效果图】", out);

	return 0;
}

int cv_blur::cvGaussianBlur()
{

	//载入原图  
	Mat image = imread("panda.jpg");

	//创建窗口  
	namedWindow("高斯滤波【原图】");
	namedWindow("高斯滤波【效果图】");

	//显示原图  
	imshow("高斯滤波【原图】", image);

	//进行均值滤波操作  
	Mat out;
	GaussianBlur(image, out, Size(7, 7), 0, 0);//第三个是内核算子,如果是一维高斯,第五个参数设置为0

	//显示效果图  
	imshow("高斯滤波【效果图】", out);

	return 0;
}

/*
* boxFilter
参数详解如下：
第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可。该函数对通道是独立处理的，且可以处理任意通道数的图片，但需要注意，待处理的图片深度应该为CV_8U, CV_16U, CV_16S, CV_32F 以及 CV_64F之一。
第二个参数，OutputArray类型的dst，即目标图像，需要和源图片有一样的尺寸和类型。
第三个参数，int类型的ddepth，输出图像的深度，-1代表使用原图深度，即src.depth()。
第四个参数，Size类型的ksize，内核的大小。一般这样写Size( w,h )来表示内核的大小( 其中，w 为像素宽度， h为像素高度)。Size（3,3）就表示3x3的核大小，Size（5,5）就表示5x5的核大小
第五个参数，Point类型的anchor，表示锚点（即被平滑的那个点），注意他有默认值Point(-1,-1)。如果这个点坐标是负值的话，就表示取核的中心为锚点，所以默认值Point(-1,-1)表示这个锚点在核的中心。
第六个参数，bool类型的normalize，默认值为true，一个标识符，表示内核是否被其区域归一化（normalized）了。
第七个参数，int类型的borderType，用于推断图像外部像素的某种边界模式。有默认值BORDER_DEFAULT，我们一般不去管它。
*/

/*
* blur
参数详解如下：
第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可。该函数对通道是独立处理的，且可以处理任意通道数的图片，但需要注意，待处理的图片深度应该为CV_8U, CV_16U, CV_16S, CV_32F 以及 CV_64F之一。
第二个参数，OutputArray类型的dst，即目标图像，需要和源图片有一样的尺寸和类型。比如可以用Mat::Clone，以源图片为模板，来初始化得到如假包换的目标图。
第三个参数，Size类型（对Size类型稍后有讲解）的ksize，内核的大小。一般这样写Size( w,h )来表示内核的大小( 其中，w 为像素宽度， h为像素高度)。Size（3,3）就表示3x3的核大小，Size（5,5）就表示5x5的核大小
第四个参数，Point类型的anchor，表示锚点（即被平滑的那个点），注意他有默认值Point(-1,-1)。如果这个点坐标是负值的话，就表示取核的中心为锚点，所以默认值Point(-1,-1)表示这个锚点在核的中心。
第五个参数，int类型的borderType，用于推断图像外部像素的某种边界模式。有默认值BORDER_DEFAULT，我们一般不去管它。
*/

/*
* GaussianBlur
参数详解如下：
第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可。它可以是单独的任意通道数的图片，但需要注意，图片深度应该为CV_8U,CV_16U, CV_16S, CV_32F 以及 CV_64F之一。
第二个参数，OutputArray类型的dst，即目标图像，需要和源图片有一样的尺寸和类型。比如可以用Mat::Clone，以源图片为模板，来初始化得到如假包换的目标图。
第三个参数，Size类型的ksize高斯内核的大小。其中ksize.width和ksize.height可以不同，但他们都必须为正数和奇数。或者，它们可以是零的，它们都是由sigma计算而来。
第四个参数，double类型的sigmaX，表示高斯核函数在X方向的的标准偏差。
第五个参数，double类型的sigmaY，表示高斯核函数在Y方向的的标准偏差。若sigmaY为零，就将它设为sigmaX，如果sigmaX和sigmaY都是0，那么就由ksize.width和ksize.height计算出来。
为了结果的正确性着想，最好是把第三个参数Size，第四个参数sigmaX和第五个参数sigmaY全部指定到。
第六个参数，int类型的borderType，用于推断图像外部像素的某种边界模式。注意它有默认值BORDER_DEFAULT。
*/
