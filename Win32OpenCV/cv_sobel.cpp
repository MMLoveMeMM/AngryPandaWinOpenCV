#include "stdafx.h"
#include "cv_sobel.h"
using namespace cv_;
using namespace cv;
cv_sobel::cv_sobel()
{
}


cv_sobel::~cv_sobel()
{
}
// 非极大值抑制实现sobel竖直细化边缘  
bool cv_sobel::SobelVerEdge(cv::Mat srcImage, cv::Mat& resultImage)
{
	CV_Assert(srcImage.channels() == 1);
	srcImage.convertTo(srcImage, CV_32FC1);
	// 水平方向的 Sobel 算子  
	cv::Mat sobelx = (cv::Mat_<float>(3, 3) << -0.125, 0, 0.125,
		-0.25, 0, 0.25,
		-0.125, 0, 0.125);
	cv::Mat ConResMat;
	// 卷积运算  
	cv::filter2D(srcImage, ConResMat, srcImage.type(), sobelx);
	// 计算梯度的幅度  
	cv::Mat graMagMat;
	cv::multiply(ConResMat, ConResMat, graMagMat);
	// 根据梯度幅度及参数设置阈值  
	int scaleVal = 4;
	double thresh = scaleVal * cv::mean(graMagMat).val[0];
	cv::Mat resultTempMat = cv::Mat::zeros(
		graMagMat.size(), graMagMat.type());
	float* pDataMag = (float*)graMagMat.data;
	float* pDataRes = (float*)resultTempMat.data;
	const int nRows = ConResMat.rows;
	const int nCols = ConResMat.cols;
	for (int i = 1; i != nRows - 1; ++i) {
		for (int j = 1; j != nCols - 1; ++j) {
			// 计算该点梯度与水平或垂直梯度值大小比较结果  
			bool b1 = (pDataMag[i * nCols + j] > pDataMag[i * nCols + j - 1]);
			bool b2 = (pDataMag[i * nCols + j] > pDataMag[i * nCols + j + 1]);
			bool b3 = (pDataMag[i * nCols + j] > pDataMag[(i - 1) * nCols + j]);
			bool b4 = (pDataMag[i * nCols + j] > pDataMag[(i + 1) * nCols + j]);
			// 判断邻域梯度是否满足大于水平或垂直梯度  
			// 并根据自适应阈值参数进行二值化  
			pDataRes[i * nCols + j] = 255 * ((pDataMag[i * nCols + j] > thresh) &&
				((b1 && b2) || (b3 && b4)));
		}
	}
	resultTempMat.convertTo(resultTempMat, CV_8UC1);
	resultImage = resultTempMat.clone();
	return true;
}

// 图像直接卷积实现sobel  
bool cv_sobel::sobelEdge(const cv::Mat&  srcImage, cv::Mat& resultImage, uchar threshold)
{
	CV_Assert(srcImage.channels() == 1);
	// 初始化水平核因子  
	Mat sobelx = (Mat_<double>(3, 3) << 1, 0, -1, 2, 0, -2, 1, 0, -1);
	// 初始化垂直核因子  
	Mat sobely = (Mat_<double>(3, 3) << 1, 2, 1, 0, 0, 0, -1, -2, -1);
	resultImage = Mat::zeros(srcImage.rows - 2,
		srcImage.cols - 2, srcImage.type());
	double edgeX = 0;
	double edgeY = 0;
	double graMag = 0;
	for (int k = 1; k < srcImage.rows - 1; ++k) {
		for (int n = 1; n < srcImage.cols - 1; ++n) {
			edgeX = 0;
			edgeY = 0;
			// 遍历计算水平与垂直梯度  
			for (int i = -1; i <= 1; ++i) {
				for (int j = -1; j <= 1; ++j) {
					edgeX += srcImage.at<uchar>(k + i, n + j) *
						sobelx.at<double>(1 + i, 1 + j);
					edgeY += srcImage.at<uchar>(k + i, n + j) *
						sobely.at<double>(1 + i, 1 + j);
				}
			}
			// 计算梯度模长  
			graMag = sqrt(pow(edgeY, 2) + pow(edgeX, 2));
			// 二值化  
			resultImage.at<uchar>(k - 1, n - 1) =
				((graMag > threshold) ? 255 : 0);
		}
	}
	return true;
}

int cv_sobel::cvsobel()
{
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y, dst;

	//【1】载入原始图    
	Mat src = imread("panda.jpg");  //工程目录下应该有一张名为1.jpg的素材图  

	//【2】显示原始图   
	imshow("sobel边缘检测 原始图", src);

	//【3】求 X方向梯度  
	Sobel(src, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	imshow("X方向Sobel 效果图", abs_grad_x);

	//【4】求Y方向梯度  
	Sobel(src, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);
	imshow("Y方向Sobel 效果图", abs_grad_y);

	//【5】合并梯度(近似)  
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
	imshow("整体方向Sobel 效果图", dst);

	return 0;
}

/*
* 拉普拉斯算子
*/
int cv_sobel::cvlaplacian()
{
	Mat src, src_gray, dst, abs_dst;

	//【1】载入原始图    
	src = imread("timg.jpg");  //工程目录下应该有一张名为1.jpg的素材图  

	//【2】显示原始图   
	imshow("图像Laplace变换 原始图", src);

	//【3】使用高斯滤波消除噪声  
	// 这个地方主要是加深边界线,要想看清线,核最好是size = 3的
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

	//【4】转换为灰度图  
	cvtColor(src, src_gray, CV_RGB2GRAY);

	//【5】使用Laplace函数  
	Laplacian(src_gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);

	//【6】计算绝对值，并将结果转换成8位  
	convertScaleAbs(dst, abs_dst);

	//【7】显示效果图  
	imshow("图像Laplace变换 效果图", abs_dst);

	return -1;
}

int cv_sobel::cvscharr()
{
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y, dst;

	//【1】载入原始图    
	Mat src = imread("panda.jpg");  //工程目录下应该有一张名为1.jpg的素材图  

	//【2】显示原始图   
	imshow("Scharr滤波器 原始图", src);

	//【3】求 X方向梯度  
	Scharr(src, grad_x, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	imshow("X方向Scharr 效果图", abs_grad_x);

	//【4】求Y方向梯度  
	Scharr(src, grad_y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);
	imshow("Y方向Scharr 效果图", abs_grad_y);

	//【5】合并梯度(近似)  
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);

	//【6】显示效果图  
	imshow("合并梯度后Scharr 效果图", dst);

	return -1;
}




/*
API 函数:
Sobel 函数
第一个参数，InputArray 类型的src，为输入图像，填Mat类型即可。
第二个参数，OutputArray类型的dst，即目标图像，函数的输出参数，需要和源图片有一样的尺寸和类型。
第三个参数，int类型的ddepth，输出图像的深度，支持如下src.depth()和ddepth的组合：
若src.depth() = CV_8U, 取ddepth =-1/CV_16S/CV_32F/CV_64F
若src.depth() = CV_16U/CV_16S, 取ddepth =-1/CV_32F/CV_64F
若src.depth() = CV_32F, 取ddepth =-1/CV_32F/CV_64F
若src.depth() = CV_64F, 取ddepth = -1/CV_64F
第四个参数，int类型dx，x 方向上的差分阶数。
第五个参数，int类型dy，y方向上的差分阶数。
第六个参数，int类型ksize，有默认值3，表示Sobel核的大小;必须取1，3，5或7。
第七个参数，double类型的scale，计算导数值时可选的缩放因子，默认值是1，表示默认情况下是没有应用缩放的。我们可以在文档中查阅getDerivKernels的相关介绍，来得到这个参数的更多信息。
第八个参数，double类型的delta，表示在结果存入目标图（第二个参数dst）之前可选的delta值，有默认值0。
第九个参数， int类型的borderType，我们的老朋友了（万年是最后一个参数），边界模式，默认值为BORDER_DEFAULT。这个参数可以在官方文档中borderInterpolate处得到更详细的信息。
*/