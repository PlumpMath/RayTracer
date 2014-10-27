#pragma once

#include "Material.h"
#include "Shape.h"
#include "Primitive.h"

//#include "BoundingBox.h"

class GeometricPrimitive
	: public Primitive
{
protected:
	//Transformation objToWorld, worldToObj;
    Shape* shape;
    Material material;

	BoundingBox boundingBox;
public:
	//Constructor
	GeometricPrimitive(Shape* s,const Material & mat);	//temp test
	~GeometricPrimitive();

	virtual bool intersect(Ray& ray, float& t_hit, Intersection& in);
    virtual bool intersectP(Ray& ray);
    virtual void getBRDF(LocalGeo& local, BRDF& brdf);

	void initBoundingBox();
	virtual BoundingBox& getBoundingBox();
};