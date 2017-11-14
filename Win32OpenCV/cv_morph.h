#pragma once
/*
ÐÎÌ¬Ñ§
*/
namespace panda
{
class cv_morph
{
public:
	cv_morph();
	~cv_morph();
public:
	static int cvdilate();
	static int cverode();
	static int cvmorphopen();
	static int cvmorphclose();
	static int cvmorphgradient();
};
}


