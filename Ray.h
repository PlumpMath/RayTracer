#pragma once

#include "Eigen/Dense"

#include "Point.h"
#include <limits>

using namespace Eigen;
using namespace std;

//#define MY_FLOAT_MAX 3.4e+38F
//#define MY_FLOAT_MIN -1e+38F
#define MY_FLOAT_MAX (numeric_limits<float>::max())
#define MY_FLOAT_MIN (-numeric_limits<float>::max())

class Ray
{
protected:
	//p(t) = e + t.dir
	Point pos;	//e_point
	Vector3f dir;	//direction

	Vector3f inv_dir;	//(1/dir_x,1/dir_y,1/dir_z)
						//for bounding box 

	//t_min <= t <= t_max
	float t_min;
	float t_max;
public:

	void buildInvDir()
	{
		//? /0?
		inv_dir = Vector3f(1.0/dir(0),1.0/dir(1),1.0/dir(2));
	}

	Ray():pos(),dir(1,0.0,0.0),t_min(0), t_max(MY_FLOAT_MAX)
	{
		buildInvDir();
	}

	Ray(const Point & position, const Vector3f & direction)
		:pos(position),dir(direction.normalized())
		,t_min(0), t_max(MY_FLOAT_MAX)
	{
		//? direction normalize?
		//dir.normalize();
		buildInvDir();
	}

	Point getStartPosition()const{return pos;}
	Vector3f getDirection()const{return dir;}
	Vector3f getInvDirection()const{return inv_dir;}

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