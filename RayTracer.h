#pragma once

#include "Eigen/Dense"

#include "Color.h"
#include "Ray.h"

#include "Shape.h"
#include "Primitive.h"

using namespace Eigen;
using namespace std;


class RayTracer
{
protected:
	int depth_max;

public:

	//TODO: Constructor
	RayTracer(int depthMax = 5):depth_max(depthMax)
	{
	}

	void trace(Ray & ray, Primitive * primitive, Color & color, int depth)
	{
		if (depth >= depth_max)
		{
			color += Color(0.0, 0.0, 0.0);
			return;
		}

		float t_hit;
		Intersection in;
		if(!primitive->intersect(ray,t_hit,in))
		{
			color += Color(0.0, 0.0, 0.0);
			return;
		}

		//there's a hit

		//test
		color.set(0,1,0);



		//delete in;
	}
};