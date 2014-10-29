#include "PointLight.h"

PointLight::PointLight(const Point& point,const Color& color,int falloffType = 0)
	:pos(point),intensity(color),falloff_type(falloffType)
{
}




Ray PointLight::generateLightRay(LocalGeo& local)
{
	Vector3f dir = pos - local.pos;	//point to the light source

	//?epsilon
	Point p ( local.pos + MY_EPSILON * dir);

	return Ray(p,dir);
}


Color PointLight::getLightColor(float t)
{
	//TODO
	// fall out?
	//return (1/(t+1)) * intensity;
	switch(falloff_type)
	{
	case 0:return intensity;
	case 1:return Color ((1/(t+1)) * intensity);
	case 2:return Color ((1/(t+1)*(t+1)) * intensity);
	default: abort();
	}
}