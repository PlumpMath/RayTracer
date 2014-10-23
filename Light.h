#pragma once


#include "Color.h"
#include "LocalGeo.h"
#include "Ray.h"

//abstract class light

class Light
{
public:
	virtual Ray generateLightRay(LocalGeo& local) = 0;
	virtual Color getLightColor(float t) = 0;
};