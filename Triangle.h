#pragma once

#include "Eigen/Dense"

//#include "Point.h"
#include "Shape.h"

using namespace Eigen;
using namespace std;


class Triangle : public Shape
{
protected:
	Point a,b,c;
	Vector3f x,y;	//p = a + beta*x + gama*y

	//TODO normal vector
	Normal normal;
public:
	Triangle(const Point & aa, const Point & bb, const Point & cc);
	virtual bool intersect(const Ray& ray, float & t_hit, LocalGeo& local);
	virtual bool intersectP(const Ray& ray);
};