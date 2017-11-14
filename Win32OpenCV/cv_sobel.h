#ifndef __4C6544D8_17A6_4F1F_931B_CD76F278F79D__
#define __4C6544D8_17A6_4F1F_931B_CD76F278F79D__
#include <iostream> 
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include "opencv2/imgproc/imgproc.hpp" 
namespace cv_
{

class cv_sobel
{
public:
	cv_sobel();
	~cv_sobel();

public:
	static bool sobelEdge(const cv::Mat&  srcImage, cv::Mat& resultImage, uchar threshold);
	static bool SobelVerEdge(cv::Mat srcImage, cv::Mat& resultImage);
	static int cvsobel();
	static int cvlaplacian();
	static int cvscharr();
};

}


#endif //__4C6544D8_17A6_4F1F_931B_CD76F278F79D__