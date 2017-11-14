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
	//����ԭͼ  
	Mat image = imread("panda.jpg");
	if (!image.data)
	{
		std::cout << "failed to read image !" << std::endl;
		return -1;
	}
	//��������  
	namedWindow("�����˲���ԭͼ��");
	namedWindow("�����˲���Ч��ͼ��");

	//��ʾԭͼ  
	imshow("�����˲���ԭͼ��", image);

	//�����˲�����  
	Mat out;
	/*
	* �����˲�
	*/
	boxFilter(image, out, -1, Size(5, 5));//���һ�������ǳ���Ҫ,Ҳ�Ǹ��㷨�ĺ�������,�����ں�����,��������ı�ģ���̶�

	//��ʾЧ��ͼ  
	imshow("�����˲���Ч��ͼ��", out);

	return 0;
}

int cv_blur::cvBlur()
{
	//����ԭͼ  
	Mat image = imread("panda.jpg");
	if (!image.data)
	{
		std::cout << "failed to read image !" << std::endl;
		return -1;
	}

	//��������  
	namedWindow("��ֵ�˲���ԭͼ��");
	namedWindow("��ֵ�˲���Ч��ͼ��");

	//��ʾԭͼ  
	imshow("��ֵ�˲���ԭͼ��", image);

	//���о�ֵ�˲�����  
	Mat out;
	blur(image, out, Size(7, 7));//���һ�������ǳ���Ҫ,Ҳ�Ǹ��㷨�ĺ�������,�����ں�����,��������ı�ģ���̶�

	//��ʾЧ��ͼ  
	imshow("��ֵ�˲���Ч��ͼ��", out);

	return 0;
}

int cv_blur::cvGaussianBlur()
{

	//����ԭͼ  
	Mat image = imread("panda.jpg");

	//��������  
	namedWindow("��˹�˲���ԭͼ��");
	namedWindow("��˹�˲���Ч��ͼ��");

	//��ʾԭͼ  
	imshow("��˹�˲���ԭͼ��", image);

	//���о�ֵ�˲�����  
	Mat out;
	GaussianBlur(image, out, Size(7, 7), 0, 0);//���������ں�����,�����һά��˹,�������������Ϊ0

	//��ʾЧ��ͼ  
	imshow("��˹�˲���Ч��ͼ��", out);

	return 0;
}

/*
* boxFilter
����������£�
��һ��������InputArray���͵�src������ͼ�񣬼�Դͼ����Mat��Ķ��󼴿ɡ��ú�����ͨ���Ƕ�������ģ��ҿ��Դ�������ͨ������ͼƬ������Ҫע�⣬�������ͼƬ���Ӧ��ΪCV_8U, CV_16U, CV_16S, CV_32F �Լ� CV_64F֮һ��
�ڶ���������OutputArray���͵�dst����Ŀ��ͼ����Ҫ��ԴͼƬ��һ���ĳߴ�����͡�
������������int���͵�ddepth�����ͼ�����ȣ�-1����ʹ��ԭͼ��ȣ���src.depth()��
���ĸ�������Size���͵�ksize���ں˵Ĵ�С��һ������дSize( w,h )����ʾ�ں˵Ĵ�С( ���У�w Ϊ���ؿ�ȣ� hΪ���ظ߶�)��Size��3,3���ͱ�ʾ3x3�ĺ˴�С��Size��5,5���ͱ�ʾ5x5�ĺ˴�С
�����������Point���͵�anchor����ʾê�㣨����ƽ�����Ǹ��㣩��ע������Ĭ��ֵPoint(-1,-1)���������������Ǹ�ֵ�Ļ����ͱ�ʾȡ�˵�����Ϊê�㣬����Ĭ��ֵPoint(-1,-1)��ʾ���ê���ں˵����ġ�
������������bool���͵�normalize��Ĭ��ֵΪtrue��һ����ʶ������ʾ�ں��Ƿ��������һ����normalized���ˡ�
���߸�������int���͵�borderType�������ƶ�ͼ���ⲿ���ص�ĳ�ֱ߽�ģʽ����Ĭ��ֵBORDER_DEFAULT������һ�㲻ȥ������
*/

/*
* blur
����������£�
��һ��������InputArray���͵�src������ͼ�񣬼�Դͼ����Mat��Ķ��󼴿ɡ��ú�����ͨ���Ƕ�������ģ��ҿ��Դ�������ͨ������ͼƬ������Ҫע�⣬�������ͼƬ���Ӧ��ΪCV_8U, CV_16U, CV_16S, CV_32F �Լ� CV_64F֮һ��
�ڶ���������OutputArray���͵�dst����Ŀ��ͼ����Ҫ��ԴͼƬ��һ���ĳߴ�����͡����������Mat::Clone����ԴͼƬΪģ�壬����ʼ���õ���ٰ�����Ŀ��ͼ��
������������Size���ͣ���Size�����Ժ��н��⣩��ksize���ں˵Ĵ�С��һ������дSize( w,h )����ʾ�ں˵Ĵ�С( ���У�w Ϊ���ؿ�ȣ� hΪ���ظ߶�)��Size��3,3���ͱ�ʾ3x3�ĺ˴�С��Size��5,5���ͱ�ʾ5x5�ĺ˴�С
���ĸ�������Point���͵�anchor����ʾê�㣨����ƽ�����Ǹ��㣩��ע������Ĭ��ֵPoint(-1,-1)���������������Ǹ�ֵ�Ļ����ͱ�ʾȡ�˵�����Ϊê�㣬����Ĭ��ֵPoint(-1,-1)��ʾ���ê���ں˵����ġ�
�����������int���͵�borderType�������ƶ�ͼ���ⲿ���ص�ĳ�ֱ߽�ģʽ����Ĭ��ֵBORDER_DEFAULT������һ�㲻ȥ������
*/

/*
* GaussianBlur
����������£�
��һ��������InputArray���͵�src������ͼ�񣬼�Դͼ����Mat��Ķ��󼴿ɡ��������ǵ���������ͨ������ͼƬ������Ҫע�⣬ͼƬ���Ӧ��ΪCV_8U,CV_16U, CV_16S, CV_32F �Լ� CV_64F֮һ��
�ڶ���������OutputArray���͵�dst����Ŀ��ͼ����Ҫ��ԴͼƬ��һ���ĳߴ�����͡����������Mat::Clone����ԴͼƬΪģ�壬����ʼ���õ���ٰ�����Ŀ��ͼ��
������������Size���͵�ksize��˹�ں˵Ĵ�С������ksize.width��ksize.height���Բ�ͬ�������Ƕ�����Ϊ���������������ߣ����ǿ�������ģ����Ƕ�����sigma���������
���ĸ�������double���͵�sigmaX����ʾ��˹�˺�����X����ĵı�׼ƫ�
�����������double���͵�sigmaY����ʾ��˹�˺�����Y����ĵı�׼ƫ���sigmaYΪ�㣬�ͽ�����ΪsigmaX�����sigmaX��sigmaY����0����ô����ksize.width��ksize.height���������
Ϊ�˽������ȷ�����룬����ǰѵ���������Size�����ĸ�����sigmaX�͵��������sigmaYȫ��ָ������
������������int���͵�borderType�������ƶ�ͼ���ⲿ���ص�ĳ�ֱ߽�ģʽ��ע������Ĭ��ֵBORDER_DEFAULT��
*/
