#pragma once

#include "Light.h"

class DirectionalLight : public Light
{
public:
	Vector3f dir;
	Color intensity;

	DirectionalLight(const Vector3f& direction,const Color& color);
	virtual Ray generateLightRay(LocalGeo& local);
	virtual Color getLightColor(float t);
};