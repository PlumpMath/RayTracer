#pragma once

#include "Color.h"
#include "LocalGeo.h"
#include "Ray.h"

using namespace std;

class BRDF
{
public:
	Color ka;	//ambient
	Color kd;	//diffuse
	Color ks;	//specular
	float shiniess;	// -v
	Color kr;	//reflection

	Color kt;	//refraction
	float ni;	//refraction index

	BRDF();
	BRDF(const Color & a,const Color & d,const Color & s,float v,const Color & r,const Color & t,float);

	Color shadingOnlyAmbient(Color& light_color);
	Color shading(LocalGeo & local, Ray & ray, Color& light_color,Vector3f & view);
};

