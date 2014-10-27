#pragma once

//#include "Eigen/Dense"

#include "Ray.h"



using namespace Eigen;
using namespace std;

class BoundingBox
{
public:
	Point min_pos;
	Vector3f length;

	Point max_pos;

	BoundingBox()
	{
	}

	BoundingBox(const Point & p,const Vector3f & l)
		:min_pos(p),length(l),max_pos(min_pos + length)
	{
	}

	BoundingBox(const Point & pmin,const Point & pmax)
		:min_pos(pmin),length(pmax - pmin),max_pos(pmax)
	{
	}

	bool IntersectP(const Ray & ray);


	Vector3f getMidPoint();
};