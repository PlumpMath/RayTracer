#pragma once

#include "Eigen/Dense"


#include "Ray.h"

using namespace Eigen;
using namespace std;

class Camera
{
protected:
	Point pos;	//camera(eye) position


public:
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