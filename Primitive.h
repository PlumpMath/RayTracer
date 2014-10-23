#pragma once

#include "Ray.h"
#include "LocalGeo.h"

#include "BRDF.h"

#include "Intersection.h"

using namespace std;


class Primitive
{
public:
	virtual bool intersect(Ray& ray, float& t_hit, Intersection & in) = 0;
    virtual bool intersectP(Ray& ray) = 0;
    virtual void getBRDF(LocalGeo& local, BRDF& brdf) = 0;
};