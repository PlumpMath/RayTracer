#pragma once

//#include "Eigen/Dense"
#include "Eigen/Geometry"

#include "Ray.h"



using namespace Eigen;
using namespace std;

class BoundingBox
{
public:
	Point min_pos;
	//Vector3f length;

	Point max_pos;

	BoundingBox()
	{
	}

	//BoundingBox(const Point & p,const Vector3f & l)
	//	:min_pos(p),max_pos(min_pos + length)  //,length(l)
	//{
	//}

	BoundingBox(const Point & pmin,const Point & pmax)
		:min_pos(pmin),max_pos(pmax)		//,,length(pmax - pmin)
	{
	}

	BoundingBox(const Point & pmin,const Point & pmax, const Affine3f & t);

	bool IntersectP(const Ray & ray);


	Vector3f getMidPoint();

	//void transform(Affine3f & t);
};