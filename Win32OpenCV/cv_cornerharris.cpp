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
	imshow("原始图", srcImage);

	//进行Harris角点检测找出角点  
	Mat cornerStrength;
	cornerHarris(srcImage, cornerStrength, 2, 3, 0.01);

	//对灰度图进行阈值操作，得到二值图并显示    
	Mat harrisCorner;
	threshold(cornerStrength, harrisCorner, 0.00001, 255, THRESH_BINARY);
	imshow("角点检测后的二值效果图", harrisCorner);

	return 0;
}

/*
* API 函数:
cornerHarris函数:
第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可，且需为单通道8位或者浮点型图像。
第二个参数，OutputArray类型的dst，函数调用后的运算结果存在这里，即这个参数用于存放Harris角点检测的输出结果，和源图片有一样的尺寸和类型。
第三个参数，int类型的blockSize，表示邻域的大小，更多的详细信息在cornerEigenValsAndVecs（）中有讲到。
第四个参数，int类型的ksize，表示Sobel()算子的孔径大小。
第五个参数，double类型的k，Harris参数。
第六个参数，int类型的borderType，图像像素的边界模式，注意它有默认值BORDER_DEFAULT。更详细的解释，参考borderInterpolate( )函数。

threshold函数 :
第一个参数，InputArray类型的src，输入数组，填单通道 , 8或32位浮点类型的Mat即可。
第二个参数，OutputArray类型的dst，函数调用后的运算结果存在这里，即这个参数用于存放输出结果，且和第一个参数中的Mat变量有一样的尺寸和类型。
第三个参数，double类型的thresh，阈值的具体值。
第四个参数，double类型的maxval，当第五个参数阈值类型type取 CV_THRESH_BINARY 或CV_THRESH_BINARY_INV 阈值类型时的最大值.
第五个参数，int类型的type，阈值类型,。threshold( )函数支持的对图像取阈值的方法由其确定，具体用法如下图：

*/