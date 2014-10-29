#pragma once

#include "Eigen/Dense"
#include "Eigen/Geometry"

//#include "Point.h"
#include "Shape.h"

using namespace Eigen;
using namespace std;


class Sphere : public Shape
{
protected:
	Point c;
	float r;

	Transform<float,3,Affine> t;	//ellipsoid(world) to sph
	Matrix3f t_normal;

	BoundingBox bb;
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	Sphere(const Point &,float,const Transform<float,3,Affine> &);
	virtual bool intersect(const Ray& ray, float & t_hit, LocalGeo& local);
	virtual bool intersectP(const Ray& ray);

	virtual BoundingBox getBoundingBox();
};