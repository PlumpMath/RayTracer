#pragma once

#include "BRDF.h"
#include "LocalGeo.h"

class Material
{
protected:
	BRDF constantBRDF;
public:

	Material()
	{
		//default, all black
	}

	Material(const BRDF & brdf):constantBRDF(brdf)
	{
	}

	void getBRDF(const LocalGeo& local, BRDF& brdf)const
	{
		brdf = constantBRDF;
	}
};