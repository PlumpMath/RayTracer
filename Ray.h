#pragma once

#include "Eigen/Dense"

#include "Point.h"

using namespace Eigen;
using namespace std;


class Ray
{
protected:
	//p(t) = e + t.dir
	Point pos;	//e_point
	Vector3f dir;	//direction

	//t_min <= t <= t_max
	float t_min;
	float t_max;
public:

	Ray():pos(),dir(0,0,0),t_min(0), t_max(FLT_MAX)
	{
	}

	Ray(const Point & position, const Vector3f & direction)
		:pos(position),dir(direction)
		,t_min(0), t_max(FLT_MAX)
	{
		//? direction normalize?
		dir.normalize();
	}

	Point getStartPosition()const{return pos;}
	Vector3f getDirection()const{return dir;}

	Point getPosition(float t)const
	{
		if ( t > t_min && t < t_max)
		{
			return Point(pos + t * dir);
		}
		//cout<<"class Ray: getPosition exceptions!";
		abort();
		return Point(0,0,0);
	}

	bool isValidT(float t)const
	{
		return (t>t_min && t<t_max);
	}
};