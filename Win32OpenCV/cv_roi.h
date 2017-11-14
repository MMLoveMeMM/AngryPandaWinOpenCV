#pragma once
namespace panda
{
class cv_roi
{
public:
	cv_roi();
	~cv_roi();
public:
	static int roiImage();
	static int blendImage();
	static int roilinearImage();
};
}


