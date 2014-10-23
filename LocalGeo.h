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

	Vector3f getReflectDirection(Vector3f in_light)
	{
		//in_light should have been normalized
		//in_light should point to light source
		//( n_normal*(2*n_light.dot(n_normal)) ) - n_light;
		return  (n * ( 2 * in_light.dot(n) ) - in_light);
	}
};