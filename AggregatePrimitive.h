#pragma once

#include <vector>

#include "Shape.h"
#include "Primitive.h"

using namespace std;

class AggregatePrimitive
	:public Primitive
{
	vector<Primitive*> vec_primitive;

public:
	//Constructor

	virtual bool intersect(Ray& ray, float& t_hit, Intersection & in);
    virtual bool intersectP(Ray& ray);
    virtual void getBRDF(LocalGeo& local, BRDF* brdf);
};