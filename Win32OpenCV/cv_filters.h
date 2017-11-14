#pragma once
namespace panda
{
class cv_filters
{
public:
	cv_filters();
	~cv_filters();
public:
	static int mediumfilter();
	static int cvbilateralFilter();
};
}


