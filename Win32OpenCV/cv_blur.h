#pragma once
namespace panda
{
class cv_blur
{
public:
	cv_blur();
	~cv_blur();
public:
	static int cvBoxBlur();
	static int cvBlur();
	static int cvGaussianBlur();
};
}


