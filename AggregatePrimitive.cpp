#include <iostream>
#include "AggregatePrimitive.h"

AggregatePrimitive::AggregatePrimitive()
{
}


AggregatePrimitive::AggregatePrimitive(vector<Primitive*> & list)
	:vec_primitive(list)
{
}

AggregatePrimitive::~AggregatePrimitive()
{
	vector<Primitive*>::iterator iter;
	for (iter = vec_primitive.begin(); iter != vec_primitive.end() ; ++iter)
	{
		if((*iter) != NULL)
		{
			delete (*iter);
			(*iter) = NULL;
		}
	}
}


bool AggregatePrimitive::intersect(Ray& ray, float& t_hit, Intersection & in)
{
	//no optimization
	//simple iteration
	bool is_hit = false;

	vector<Primitive*>::iterator iter;
	t_hit = FLT_MAX;
	for (iter = vec_primitive.begin();iter != vec_primitive.end(); ++iter)
	{
		float this_t;
		Intersection this_in;
		bool is_this_hit = (*iter)->intersect(ray,this_t,this_in);
		
		is_hit = is_hit || is_this_hit;

		if(is_this_hit && this_t < t_hit)
		{
			t_hit = this_t;
			in = this_in;
			in.primitive = (*iter);
		}
	}

	return is_hit;
}


bool AggregatePrimitive::intersectP(Ray& ray)
{
	vector<Primitive*>::iterator iter;
	bool is_hit = false;
	for (iter = vec_primitive.begin();iter != vec_primitive.end(); ++iter)
	{
		is_hit = (*iter)->intersectP(ray);

		if (is_hit)
		{
			return true;
		}
	}
	return is_hit;
}


void AggregatePrimitive::getBRDF(LocalGeo& local, BRDF& brdf)
{
	// This should never get called, because in->primitive will
	// never be an aggregate primitive
	cout<<"error: AggregatePrimitive shouldn't be called ever\n";
	abort();
}
