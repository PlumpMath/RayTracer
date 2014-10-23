#pragma once

#include "Eigen/Dense"


#include "Ray.h"

using namespace Eigen;
using namespace std;

class Camera
{
public:
	Point pos;	//camera(eye) position



	Camera(const Vector3f & p):pos(p)
	{
	}

	/*
	Camera(const Camera & c):pos(c.pos)
	{
	}
	*/

	//?
	Ray generateRay(const Point & sample_point)
	{
		return Ray(pos, sample_point - pos);
	}


};