#pragma once

//#include "Eigen/Dense"

#include "Point.h"

using namespace Eigen;
using namespace std;


class Transformation
	:public Matrix4f
{
public:




	Vector3f transform(const Vector3f & p)
	{
		Vector4f hp(p(0),p(1),p(2),1);
		hp = (*this) * hp;
		hp = hp/hp(3);
		Vector3f rp(hp(0),hp(1),hp(2));
		return rp;
	}

};