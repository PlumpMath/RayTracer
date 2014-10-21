#pragma once

#include "Shape.h"
#include "Primitive.h"

class GeometricPrimitive
	: public Primitive
{
protected:
	//Transformation objToWorld, worldToObj;
    Shape* shape;
    //Material* mat;
public:
	//Constructor
	GeometricPrimitive(Shape* s);	//temp test
	~GeometricPrimitive();

	virtual bool intersect(Ray& ray, float& t_hit, Intersection& in);
    virtual bool intersectP(Ray& ray);
    virtual void getBRDF(LocalGeo& local, BRDF* brdf);
};