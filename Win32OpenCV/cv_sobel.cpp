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
// �Ǽ���ֵ����ʵ��sobel��ֱϸ����Ե  
bool cv_sobel::SobelVerEdge(cv::Mat srcImage, cv::Mat& resultImage)
{
	CV_Assert(srcImage.channels() == 1);
	srcImage.convertTo(srcImage, CV_32FC1);
	// ˮƽ����� Sobel ����  
	cv::Mat sobelx = (cv::Mat_<float>(3, 3) << -0.125, 0, 0.125,
		-0.25, 0, 0.25,
		-0.125, 0, 0.125);
	cv::Mat ConResMat;
	// �������  
	cv::filter2D(srcImage, ConResMat, srcImage.type(), sobelx);
	// �����ݶȵķ���  
	cv::Mat graMagMat;
	cv::multiply(ConResMat, ConResMat, graMagMat);
	// �����ݶȷ��ȼ�����������ֵ  
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
			// ����õ��ݶ���ˮƽ��ֱ�ݶ�ֵ��С�ȽϽ��  
			bool b1 = (pDataMag[i * nCols + j] > pDataMag[i * nCols + j - 1]);
			bool b2 = (pDataMag[i * nCols + j] > pDataMag[i * nCols + j + 1]);
			bool b3 = (pDataMag[i * nCols + j] > pDataMag[(i - 1) * nCols + j]);
			bool b4 = (pDataMag[i * nCols + j] > pDataMag[(i + 1) * nCols + j]);
			// �ж������ݶ��Ƿ��������ˮƽ��ֱ�ݶ�  
			// ����������Ӧ��ֵ�������ж�ֵ��  
			pDataRes[i * nCols + j] = 255 * ((pDataMag[i * nCols + j] > thresh) &&
				((b1 && b2) || (b3 && b4)));
		}
	}
	resultTempMat.convertTo(resultTempMat, CV_8UC1);
	resultImage = resultTempMat.clone();
	return true;
}

// ͼ��ֱ�Ӿ��ʵ��sobel  
bool cv_sobel::sobelEdge(const cv::Mat&  srcImage, cv::Mat& resultImage, uchar threshold)
{
	CV_Assert(srcImage.channels() == 1);
	// ��ʼ��ˮƽ������  
	Mat sobelx = (Mat_<double>(3, 3) << 1, 0, -1, 2, 0, -2, 1, 0, -1);
	// ��ʼ����ֱ������  
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
			// ��������ˮƽ�봹ֱ�ݶ�  
			for (int i = -1; i <= 1; ++i) {
				for (int j = -1; j <= 1; ++j) {
					edgeX += srcImage.at<uchar>(k + i, n + j) *
						sobelx.at<double>(1 + i, 1 + j);
					edgeY += srcImage.at<uchar>(k + i, n + j) *
						sobely.at<double>(1 + i, 1 + j);
				}
			}
			// �����ݶ�ģ��  
			graMag = sqrt(pow(edgeY, 2) + pow(edgeX, 2));
			// ��ֵ��  
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

	//��1������ԭʼͼ    
	Mat src = imread("panda.jpg");  //����Ŀ¼��Ӧ����һ����Ϊ1.jpg���ز�ͼ  

	//��2����ʾԭʼͼ   
	imshow("sobel��Ե��� ԭʼͼ", src);

	//��3���� X�����ݶ�  
	Sobel(src, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	imshow("X����Sobel Ч��ͼ", abs_grad_x);

	//��4����Y�����ݶ�  
	Sobel(src, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);
	imshow("Y����Sobel Ч��ͼ", abs_grad_y);

	//��5���ϲ��ݶ�(����)  
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
	imshow("���巽��Sobel Ч��ͼ", dst);

	return 0;
}

/*
* ������˹����
*/
int cv_sobel::cvlaplacian()
{
	Mat src, src_gray, dst, abs_dst;

	//��1������ԭʼͼ    
	src = imread("timg.jpg");  //����Ŀ¼��Ӧ����һ����Ϊ1.jpg���ز�ͼ  

	//��2����ʾԭʼͼ   
	imshow("ͼ��Laplace�任 ԭʼͼ", src);

	//��3��ʹ�ø�˹�˲���������  
	// ����ط���Ҫ�Ǽ���߽���,Ҫ�뿴����,�������size = 3��
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

	//��4��ת��Ϊ�Ҷ�ͼ  
	cvtColor(src, src_gray, CV_RGB2GRAY);

	//��5��ʹ��Laplace����  
	Laplacian(src_gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);

	//��6���������ֵ���������ת����8λ  
	convertScaleAbs(dst, abs_dst);

	//��7����ʾЧ��ͼ  
	imshow("ͼ��Laplace�任 Ч��ͼ", abs_dst);

	return -1;
}

int cv_sobel::cvscharr()
{
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y, dst;

	//��1������ԭʼͼ    
	Mat src = imread("panda.jpg");  //����Ŀ¼��Ӧ����һ����Ϊ1.jpg���ز�ͼ  

	//��2����ʾԭʼͼ   
	imshow("Scharr�˲��� ԭʼͼ", src);

	//��3���� X�����ݶ�  
	Scharr(src, grad_x, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	imshow("X����Scharr Ч��ͼ", abs_grad_x);

	//��4����Y�����ݶ�  
	Scharr(src, grad_y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);
	imshow("Y����Scharr Ч��ͼ", abs_grad_y);

	//��5���ϲ��ݶ�(����)  
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);

	//��6����ʾЧ��ͼ  
	imshow("�ϲ��ݶȺ�Scharr Ч��ͼ", dst);

	return -1;
}




/*
API ����:
Sobel ����
��һ��������InputArray ���͵�src��Ϊ����ͼ����Mat���ͼ��ɡ�
�ڶ���������OutputArray���͵�dst����Ŀ��ͼ�񣬺����������������Ҫ��ԴͼƬ��һ���ĳߴ�����͡�
������������int���͵�ddepth�����ͼ�����ȣ�֧������src.depth()��ddepth����ϣ�
��src.depth() = CV_8U, ȡddepth =-1/CV_16S/CV_32F/CV_64F
��src.depth() = CV_16U/CV_16S, ȡddepth =-1/CV_32F/CV_64F
��src.depth() = CV_32F, ȡddepth =-1/CV_32F/CV_64F
��src.depth() = CV_64F, ȡddepth = -1/CV_64F
���ĸ�������int����dx��x �����ϵĲ�ֽ�����
�����������int����dy��y�����ϵĲ�ֽ�����
������������int����ksize����Ĭ��ֵ3����ʾSobel�˵Ĵ�С;����ȡ1��3��5��7��
���߸�������double���͵�scale�����㵼��ֵʱ��ѡ���������ӣ�Ĭ��ֵ��1����ʾĬ���������û��Ӧ�����ŵġ����ǿ������ĵ��в���getDerivKernels����ؽ��ܣ����õ���������ĸ�����Ϣ��
�ڰ˸�������double���͵�delta����ʾ�ڽ������Ŀ��ͼ���ڶ�������dst��֮ǰ��ѡ��deltaֵ����Ĭ��ֵ0��
�ھŸ������� int���͵�borderType�����ǵ��������ˣ����������һ�����������߽�ģʽ��Ĭ��ֵΪBORDER_DEFAULT��������������ڹٷ��ĵ���borderInterpolate���õ�����ϸ����Ϣ��
*/