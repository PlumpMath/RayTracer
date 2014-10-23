#pragma once

#include <vector>

#include "Shape.h"
#include "Primitive.h"

using namespace std;

class AggregatePrimitive
	:public Primitive
{
protected:
	vector<Primitive*> vec_primitive;

public:
	//Constructor
	AggregatePrimitive();
	AggregatePrimitive(vector<Primitive*> & list);
	~AggregatePrimitive();

	//add primitive?

	virtual bool intersect(Ray& ray, float& t_hit, Intersection & in);
    virtual bool intersectP(Ray& ray);
    virtual void getBRDF(LocalGeo& local, BRDF& brdf);
};