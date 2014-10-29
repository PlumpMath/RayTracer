#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const Vector3f& direction,const Color& color)
	:dir(direction.normalized()),intensity(color)
{
}


//this function is generating a shadow light ray
Ray DirectionalLight::generateLightRay(LocalGeo& local)
{

	//?epsilon
	Point p ( local.pos - MY_EPSILON * dir);

	return Ray(p,-dir);
}

Color DirectionalLight::getLightColor(float t)
{
	return intensity;
}