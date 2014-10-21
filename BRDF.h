#pragma once

#include "Color.h"

class BRDF
{
public:
	Color ka;	//ambient
	Color kd;	//diffuse
	Color ks;	//specular
	float shiniess;	// -v
	Color kr;	//reflection
};