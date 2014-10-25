#pragma once

#include "Light.h"

//enum PointLightFallOffType
//{
//	falloff_none
//	,falloff_linear
//	,falloff_quadratic
//}


class PointLight : public Light
{
public:
	Point pos;
	Color intensity;
	int falloff_type;

	PointLight(const Point& point,const Color& color,int falloffType);
	virtual Ray generateLightRay(LocalGeo& local);
	virtual Color getLightColor(float t);
};