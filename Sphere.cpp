#include "Sphere.h"
#include <math.h>
#include <iostream>

#define FLOAT_EPSILON 0.001


Sphere::Sphere(const Point & center, float radius,const Transform<float,3,Affine> & tt)	//,const Transform<float,3,Affine> & scale_tt,const Transform<float,3,Affine> & translate_tt
	:c(center),r(radius),t(tt.inverse()),t_normal(tt.linear().inverse().transpose())
{

	Vector3f rr(r,r,r);

	Point min_pos( c - rr);
	Point max_pos( c + rr);
	
	bb = BoundingBox(min_pos,max_pos,tt);

}

bool Sphere::intersect(const Ray & init_ray, float & t_hit, LocalGeo& local)
{
	//Transformation
	Vector3f e( t * ( init_ray.getStartPosition()).colwise().homogeneous());
	Vector3f d(  t.linear() * ( init_ray.getDirection()));
	Ray ray(Point(e),d);



	////////////////////////////////
	//Vector3f e(ray.getStartPosition());	//?type
	//Vector3f d(ray.getDirection());

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

			Point p_sph(ray.getPosition(t_hit));	//sphere coordinate
			Point p(init_ray.getPosition(t_hit));


			//TODO problems: here
			//Be careful: Normal transform!!!!
			//Affine3f M_sph2world(t.inverse(Affine));
			//Point p_sph( M_sph2world * p.colwise().homogeneous() );


			//Affine3f tt(t.matrix().transpose());
			//Normal n(  tt.linear()*(p_sph - c) );


			Normal n( t_normal * (p_sph - c) );

			local = LocalGeo(p, n);



			//return true;
			return ray.isValidT(t_hit);
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


bool Sphere::intersectP(const Ray& init_ray)
{
	//Transformation
	Vector3f e( t * ( init_ray.getStartPosition()).colwise().homogeneous());
	Vector3f d(  t.linear() * ( init_ray.getDirection()) );
	Ray ray(Point(e),d);


	//? t<0?
	//Vector3f e(ray.getStartPosition());	//?type
	//Vector3f d(ray.getDirection());

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



BoundingBox Sphere::getBoundingBox()
{
	////no ellipsoid
	//Vector3f offset(r,r,r);
	//Point min_pos(c - offset);
	//return BoundingBox(min_pos,(2*offset));


	return bb;
}