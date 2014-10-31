#pragma once

#include <vector>

#include "Point.h"
#include "LocalGeo.h"
#include "Ray.h"
#include "Color.h"

//enum PointLightFallOffType
//{
//	falloff_none
//	,falloff_linear
//	,falloff_quadratic
//}


class AreaLight
{
protected:
	Point center;
	Vector3f half_length_u;
	Vector3f half_length_v;
	Color intensity;
	int falloff_type;
	float rate;

	int num_samples;

	float Random0_1()
	{
		int temp;
		float r;

		temp=rand()%1000;
		r=(float)temp/1000;
		return r;
	}
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	AreaLight(const Point& point,const Vector3f & hlu,const Vector3f & hlv ,const Color& color,int samples,int falloffType);
	vector<Ray> generateLightRay(LocalGeo& local);
	Color getLightColor( float t);

	int getNumSamples()const{return num_samples;}
	float getRate()const {return rate;}
};