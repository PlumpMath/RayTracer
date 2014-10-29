#pragma once

#include "Eigen/Dense"

//#include "Point.h"
#include "Shape.h"

using namespace Eigen;
using namespace std;

enum TriangleType
{
	TT_UNI_NORMAL
	,TT_TRI_NORMAL
};


class Triangle : public Shape
{
protected:
	TriangleType tt;

	Point a,b,c;
	Vector3f x,y;	//p = a + beta*x + gama*y

	//TODO normal vector
	Normal normal;

	Normal an,bn,cn;
public:
	Triangle(const Point & aa, const Point & bb, const Point & cc);
	Triangle(const Point & aa, const Point & bb, const Point & cc,const Normal & n1,const Normal & n2,const Normal & n3);
	virtual bool intersect(const Ray& ray, float & t_hit, LocalGeo& local);
	virtual bool intersectP(const Ray& ray);

	virtual BoundingBox getBoundingBox();
};