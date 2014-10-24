#pragma once

#include "Eigen/Dense"

using namespace Eigen;
using namespace std;


class Color : public Vector3f
{
protected:
	//Vector3f vec;

public:
	Color(float r = 0.0, float g = 0.0, float b = 0.0):Vector3f(r,g,b)
	{
	}

	Color(const Vector3f &v):Vector3f(v)
	{
	}


	float r()const{return x();}
	float g()const{return y();}
	float b()const{return z();}

	void set(float r = 0.0, float g = 0.0, float b = 0.0)
	{
		(*this)(0) = r;
		(*this)(1) = g;
		(*this)(2) = b;
	}

	void set(const Color & c)
	{
		(*this)(0) = c(0);
		(*this)(1) = c(1);
		(*this)(2) = c(2);
	}

	Color componentMulti(const Color & c)
	{
		return Color(r()*c.r(), g()*c.g(), b()*c.b());
	}

	bool isPositive()const
	{
		return (r()>0.001) && (g()>0.001) && (b()>0.001);
	}
	/*
	void operator += (const Color & c)
	{
		vec += c.vec;
	}

	Color operator + (const Color & c)
	{
		return Color(vec + c.vec);
	}

	void operator -= (const Color & c)
	{
		vec -= c.vec;
	}

	Color operator - (const Color & c)
	{
		return Color(vec - c.vec);
	}
	*/
};