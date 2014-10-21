#pragma once

//#include "Eigen/Dense"


//using namespace Eigen;
using namespace std;


class Sample
{
protected:
	//Vector2f pos;		// (u,v)

public:
	float u;
	float v;
	
	Sample(float uu = 0.0, float vv = 0.0):u(uu),v(vv)
	{
	}
};