#pragma once

#include "Eigen/Dense"

#include "Sample.h"
//#include "Screen.h"


using namespace Eigen;
using namespace std;


class Sampler
{
protected:
	//Screen screen;

	//currently it should be a rectangle
	//Point?
	Vector3f ul_pos;	//upper left
	Vector3f ur_pos;	//upper right
	Vector3f ll_pos;	//lower left
	Vector3f lr_pos;	//lower right

	float pixel_length;	//default: pixel is square  (resolution)
	//float resolution_h;
	//float resolution_v;

	Vector3f horizontal_vec;
	Vector3f vertical_vec;

	int num_pixels_width;
	int num_pixels_height;


	Vector3f offset_vec;	//move to the center of pixel

	


	//current
	int y;		//y ^
	int x;		//x  ->

public:

	Sampler()
	{
	}


	Sampler(const Vector3f & ul, const Vector3f & ur, const Vector3f & lr, const Vector3f & ll, float pixelLength = 1.0)
		:ul_pos(ul),ur_pos(ur),lr_pos(lr),ll_pos(ll)
		,pixel_length(pixelLength)
		,horizontal_vec((ur_pos - ul_pos).normalized() * pixel_length)
		,vertical_vec((ll_pos - ul_pos).normalized() * pixel_length)

		,num_pixels_width((ur_pos - ul_pos).norm() / pixel_length)
		,num_pixels_height((ul_pos - ll_pos).norm() / pixel_length)

		,offset_vec(horizontal_vec/2 + vertical_vec/2)
	{
		y = 0;
		x = 0;
	}

	Vector3f getPoint(float u, float v)
	{
		u /= (float)num_pixels_width;
		u = 1 - u;
		v /= (float)num_pixels_height;
		v = 1 - v;
		return (   u * ( v * ll_pos + (1-v) * (ul_pos)) + (1 - u) * (v * lr_pos + (1-v) * ur_pos )   + offset_vec  );
	}

	int getWidth(){return num_pixels_width;}
	int getHeight(){return num_pixels_height;}


	
	//!! point better be &
	bool getSample(Vector3f & point, int &r, int &c)
	{
		
		
		if(y >= num_pixels_height )
		{
			y = 0;
			x++;
			if(x >= num_pixels_width)
			{
				return false;
			}
		}

		//point = new Vector3f(getPoint(x,y));
		point = Vector3f(getPoint(x,y));
		r = num_pixels_height - 1 - y;
		c = x;


		y++;

		return true;
	}
};