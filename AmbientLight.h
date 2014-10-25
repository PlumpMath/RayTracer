#pragma once

#include "Color.h"

class AmbientLight
{
public:
	Color intensity;

	AmbientLight(const Color & c)
		:intensity(c)
	{
	}
};