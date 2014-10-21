#include "Sphere.h"
#include <math.h>
#include <iostream>

#define FLOAT_EPSILON 0.001


Sphere::Sphere(const Point & center, float radius):c(center),r(radius)
{
}

bool Sphere::intersect(const Ray & ray, float & t_hit, LocalGeo& local)
{
	Vector3f e(ray.getStartPosition());	//?type
	Vector3f d(ray.getDirection());

	float delta = pow( d .dot (e - c)  ,2) - d.squaredNorm() * ( (e - c) .squaredNorm() - r*r )  ;

	if ( delta > FLOAT_EPSILON )
	{
		//two root, one root should be included in this
		float r_delta = sqrt(delta);

		float tmp_mdec = - ( d.dot(e - c) );

		float t_smaller = ( tmp_mdec - r_delta  ) / d.squaredNorm();
		float t_bigger = ( tmp_mdec + r_delta  ) / d.squaredNorm();

		if(t_smaller > FLOAT_EPSILON)
		{
			t_hit = t_smaller;

			Point p(ray.getPosition(t_hit));
			local = LocalGeo(p, Normal(p - c));

			return true;
		}
		//inside
		/*
		else if(t_bigger > FLOAT_EPSILON)
		{
			t_hit = t_bigger;
		}
		*/
		
	}


	t_hit = 0.0;
	//local = NULL;
	return false;
}


bool Sphere::intersectP(const Ray& ray)
{
	//? t<0?
	Vector3f e(ray.getStartPosition());	//?type
	Vector3f d(ray.getDirection());

	float delta = pow( d .dot (e - c)  ,2) - d.squaredNorm() * ( (e - c) .squaredNorm() - r*r )  ;

	if ( delta > FLOAT_EPSILON )
	{
		float r_delta = sqrt(delta);

		float tmp_mdec = - ( d.dot(e - c) );

		float t_smaller = ( tmp_mdec - r_delta  ) / d.squaredNorm();
		//float t_bigger = ( tmp_mdec + r_delta  ) / d.squaredNorm();

		if(t_smaller > FLOAT_EPSILON)
		{
			return true;
		}
	}

	return false;
}