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
};