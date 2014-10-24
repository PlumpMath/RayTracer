#include "Triangle.h"

Triangle::Triangle(const Point & aa, const Point & bb, const Point & cc)
	:a(aa),b(bb),c(cc)
	,x(b-a),y(c-a)
	,normal(x.cross(y))
{
}

bool Triangle::intersect(const Ray& ray, float & t_hit, LocalGeo& local)
{
	//Ax=b
	Vector3f d = ray.getDirection();
	Vector3f e = ray.getStartPosition();
	Matrix3f A;

	for (int i = 0; i < 3; i++)
	{
		A(i,0) = -x(i);
		A(i,1) = -y(i);
		A(i,2) = d(i);
	}

	float det_A = A.determinant();

	if(det_A != 0.0f)
	{
		Matrix3f tA = A ;
		Matrix3f betaA = A;
		Matrix3f gamaA = A;
		for (int i = 0; i < 3; i++)
		{
			betaA(i,0) = a(i) - e(i);
			gamaA(i,1) = a(i) - e(i);
			tA(i,2) = a(i) - e(i);
		}

		t_hit = tA.determinant() / det_A;

		float beta = betaA.determinant() / det_A;
		float gama = gamaA.determinant() / det_A;

		if ( ray.isValidT(t_hit) 
			&& beta >= 0.0 && gama >= 0.0
			&& beta + gama <= 1.0)
		{
			if(normal.dot(-d) > 0)
			{
				local.n = normal;
			}
			else
			{
				local.n = Normal(- normal);
			}
			
			//local.pos = ray.getPosition(t_hit);
			local.pos =(Point)( a + beta*x + gama*y );

			return true;
		}

	}

	t_hit = 0.0;
	return false;
}


bool Triangle::intersectP(const Ray& ray)
{
	LocalGeo tmp(Point(0,0,0),Normal(1,0,0));
	float tmp_f;
	return intersect(ray,tmp_f,tmp);
}