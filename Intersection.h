#pragma once

#include "LocalGeo.h"

class Primitive;

class Intersection
{
public:
	LocalGeo local;
	Primitive * primitive;

	Intersection(const Point & position = Point(0,0,0), const Normal & normal = Normal(0,0,0)):local(position,normal)
	{
		primitive = NULL;
	}
};