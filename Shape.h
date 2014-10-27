#pragma once

#include "Eigen/Dense"

#include "Ray.h"
#include "LocalGeo.h"

#include "BoundingBox.h"

using namespace Eigen;
using namespace std;

class Shape
{
public:
	virtual bool intersect(const Ray& ray, float & t_hit, LocalGeo& local) = 0;
	virtual bool intersectP(const Ray& ray) = 0;

	virtual BoundingBox getBoundingBox() = 0;
};