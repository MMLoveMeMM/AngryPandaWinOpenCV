#pragma once
namespace panda
{
class cv_hough
{
public:
	cv_hough();
	~cv_hough();
public:
	static int cvhoughlines();
	static int cvhoughlinesp();

	static int cvhoughcircles();
};
}


