#pragma once

#include "Eigen/Dense"

#include "Color.h"
#include "Ray.h"

#include "Shape.h"
#include "Primitive.h"

using namespace Eigen;
using namespace std;

class Scene;

class RayTracer
{
protected:
	int depth_max;

public:

	//TODO: Constructor
	RayTracer(int depthMax = 5):depth_max(depthMax)
	{
	}

	void trace(Scene & scene, Ray & ray, Primitive * primitive, Color & color, int depth);
	
	Ray createReflectionRay(LocalGeo & local,Ray & in_ray);
	Ray createRefractionRay(LocalGeo & local,Ray & in_ray,float nt,bool & tir);	//total internal reflection
};