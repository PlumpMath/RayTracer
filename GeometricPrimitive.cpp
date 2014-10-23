#include "GeometricPrimitive.h"


GeometricPrimitive::GeometricPrimitive(Shape* s,const Material & mat)
	:shape(s),material(mat)
{
}

GeometricPrimitive::~GeometricPrimitive()
{
	if(shape)
	{
		delete shape;
	}
	shape = NULL;
}


bool GeometricPrimitive::intersect(Ray& ray, float& t_hit, Intersection& in)
{
	//temp test
	//in = new Intersection();
	bool hit = shape->intersect(ray,t_hit,in.local);

	if(hit)
	{
		in.primitive = this;
	}
	

	return hit;
}


bool GeometricPrimitive::intersectP(Ray& ray)
{
	return shape->intersectP(ray);
}



void GeometricPrimitive::getBRDF(LocalGeo& local, BRDF & brdf)
{
	material.getBRDF(local,brdf);
}