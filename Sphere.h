#pragma once

#include "Eigen/Dense"

//#include "Point.h"
#include "Shape.h"

using namespace Eigen;
using namespace std;


class Sphere : public Shape
{
protected:
	Point c;
	float r;
public:
	Sphere(const Point &,float);
	virtual bool intersect(const Ray& ray, float & t_hit, LocalGeo& local);
	virtual bool intersectP(const Ray& ray);

	virtual BoundingBox getBoundingBox();
};