#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const Vector3f& direction,const Color& color)
	:dir(direction.normalized()),intensity(color)
{
}


Ray DirectionalLight::generateLightRay(LocalGeo& local)
{

	//?epsilon
	Point p ( local.pos - 0.0001 * dir);

	return Ray(p,-dir);
}

Color DirectionalLight::getLightColor(float t)
{
	return intensity;
}