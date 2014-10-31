#include "AreaLight.h"

AreaLight::AreaLight(const Point& c,const Vector3f & hlu,const Vector3f & hlv ,const Color& color,int samples,int falloffType = 0)
	:center(c),half_length_u(hlu),half_length_v(hlv)
	,intensity(color),falloff_type(falloffType)
	,num_samples(samples)
	,rate(1/((float)samples))
{
}




vector<Ray> AreaLight::generateLightRay(LocalGeo& local)
{
	vector<Ray> vec_ray;

	Vector3f center_dir = center - local.pos;	//point to the center of light source

	for(int i = 0 ; i < num_samples ; i++)
	{
		Vector3f dir = center_dir 
			+ 2*(Random0_1() - 0.5 ) * half_length_u 
			+ 2*(Random0_1() - 0.5 ) * half_length_v;
		Point p( local.pos + MY_EPSILON * dir);
		vec_ray.push_back( Ray(p,dir) );
	}



	return vec_ray;
}


Color AreaLight::getLightColor(float t)
{
	//rate percent of shadow ray that hit the arealight

	switch(falloff_type)
	{
	case 0:return Color(intensity);
	case 1:return Color ((1/(t+1)) * intensity);
	case 2:return Color ((1/(t+1)*(t+1)) * intensity);
	default: abort();
	}
}