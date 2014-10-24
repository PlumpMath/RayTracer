#include "PointLight.h"

PointLight::PointLight(const Point& point,const Color& color)
	:pos(point),intensity(color)
{
}




Ray PointLight::generateLightRay(LocalGeo& local)
{
	Vector3f dir = pos - local.pos;	//point to the light source

	//?epsilon
	Point p = local.pos + 0.0001 * dir;

	return Ray(p,dir);
}


Color PointLight::getLightColor(float t)
{
	//TODO
	// fall out?
	//return (1/(t+1)) * intensity;

	return intensity;
}