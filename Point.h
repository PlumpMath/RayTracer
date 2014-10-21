#pragma once

#include "Eigen/Dense"


using namespace Eigen;
using namespace std;

class Point : public Vector3f
{
public:
	Point(float x = 0.0, float y = 0.0, float z = 0.0):Vector3f(x,y,z)
	{
	}

	Point(const Vector3f &v):Vector3f(v)
	{
	}
};