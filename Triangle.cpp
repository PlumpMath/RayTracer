#include "Triangle.h"

Triangle::Triangle(const Point & aa, const Point & bb, const Point & cc)
	:a(aa),b(bb),c(cc)
	,x(b-a),y(c-a)
	,normal(x.cross(y))
	,tt(TT_UNI_NORMAL)
{
}

Triangle::Triangle(const Point & aa, const Point & bb, const Point & cc,const Normal & n1,const Normal & n2,const Normal & n3)
	:a(aa),b(bb),c(cc)
	,x(b-a),y(c-a)
	,an(n1),bn(n2),cn(n3)
	,tt(TT_TRI_NORMAL)
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
			//local.pos = ray.getPosition(t_hit);
			local.pos =(Point)( a + beta*x + gama*y );
			//local.pos =(Point)( (1-beta-gama)*a + beta*b + gama*c );


			if(tt == TT_UNI_NORMAL)
			{
				//note: making sure the triangle will be seen
				//if using obj file, this should be deleted
				if(normal.dot(-d) > 0)
				{
					local.n = normal;
				}
				else
				{
					local.n = Normal(- normal);
				}
			}
			else
			{
				//TRI NORMAL
				//TODO
				Normal i_n((1-beta-gama)*an + beta*bn + gama*cn);
				local.n = i_n;
			}
			
			

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




BoundingBox Triangle::getBoundingBox()
{
	float minx = a(0);
	float miny = a(1);
	float minz = a(2);

	float maxx = a(0);
	float maxy = a(1);
	float maxz = a(2);


	minx = min(minx,b(0));
	miny = min(miny,b(1));
	minz = min(minz,b(2));
	minx = min(minx,c(0));
	miny = min(miny,c(1));
	minz = min(minz,c(2));

	maxx = max(maxx,b(0));
	maxy = max(maxy,b(1));
	maxz = max(maxz,b(2));
	maxx = max(maxx,c(0));
	maxy = max(maxy,c(1));
	maxz = max(maxz,c(2));


	Point min_pos(minx,miny,minz);
	Point max_pos(maxx,maxy,maxz);
	return BoundingBox(min_pos,max_pos);
}