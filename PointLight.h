#pragma once

#include "Light.h"

class PointLight : public Light
{
public:
	Point pos;
	Color intensity;

	PointLight(const Point& point,const Color& color);
	virtual Ray generateLightRay(LocalGeo& local);
	virtual Color getLightColor(float t);
};