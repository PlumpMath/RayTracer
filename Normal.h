//normal vector

#pragma once

#include "Eigen/Dense"

using namespace Eigen;
using namespace std;

class Normal: public Vector3f
{
public:
	//Vector3f vec;


	Normal(float x = 0.0, float y = 0.0, float z = 0.0):Vector3f(x,y,z)//:vec(x,y,z)
	{
		//vec.normalize();
		normalize();
	}

	Normal(const Vector3f &v):Vector3f(v)
	{
		//vec.normalize();
		normalize();
	}

};