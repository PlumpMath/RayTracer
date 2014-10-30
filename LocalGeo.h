#pragma once

#include "Eigen/Dense"

#include "Point.h"
#include "Normal.h"

using namespace Eigen;
using namespace std;


class LocalGeo
{
public:
	Point pos;
	Normal n;

	LocalGeo(const Point & position, const Normal & normal)
		:pos(position),n(normal)
	{
	}

	Vector3f getReflectDirection(const Vector3f & in_light)
	{
		//in_light should have been normalized
		//in_light should point to light source
		//( n_normal*(2*n_light.dot(n_normal)) ) - n_light;
		return  (n * ( 2 * in_light.dot(n) ) - in_light);
	}

	Vector3f getRefractionDirection(const Vector3f & I,float nn,bool & tir)
	{
		// nn = n1 / n2;
		//in_light should have been normalized
		//in_light should point to light source

		float c1 = n.dot(I);
		float delta = 1 - nn*nn * (1 - c1*c1);

		tir = (delta<=0);
		if(!tir)
		{
			float sqt = sqrt(delta);

			return Vector3f((nn*c1-sqt)*n - nn*I );
		}
		else
		{
			//total internal reflection
			//no refraction
			return Vector3f(0,0,0);
		}
	}
};