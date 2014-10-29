#include "Sampler.h"

bool Sampler::getSample(Vector3f & point, int &r, int &c)
{
	if(anti_aliasing)
	{


		if(sample_y >= samples_row)
		{
			sample_y = 0;
			sample_x++;
			if(sample_x >= samples_row)
			{
				//next pixel
				sample_y = 0;
				sample_x = 0;

				y++;
				if(y >= num_pixels_height )
				{
					y = 0;
					x++;
					if(x >= num_pixels_width)
					{
						return false;
					}
				}
			}
		}

		point = Vector3f(getPoint_AntiAliasing(x,y));
		r = num_pixels_height - 1 - y;
		c = x;

		sample_y++;

		return true;
	}
	else
	{
		//no antialiasing

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
}