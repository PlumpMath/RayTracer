#include "Film.h"

#include "loadpng/lodepng.h"
#include <iostream>

Film::Film(int w,int h)
		:image_bucket(h,vector< vector<Color> >(w,vector<Color>()))
		,width(w)
		,height(h)
{
}



Color Film::getColorAt(int row, int column)
{
	//test: one sample for one pixel

	//return colorFloat2Byte( (image_bucket.at(row).at(column))(i) );

	vector<Color>& bucket = image_bucket.at(row).at(column);

	Color cur_color(0,0,0);
	vector<Color>::iterator iter;
	for(iter = bucket.begin(); iter!= bucket.end() ;++iter)
	{
		cur_color += (*iter);
	}
	cur_color /= (float)(bucket.size());

	return cur_color;
}



void Film::commit(int row, int column, Color & color)
{
	//test
	//image_bucket.at(row).at(column).set(color);

	image_bucket.at(row).at(column).push_back(color);
}


void Film::generateImgVector(vector<unsigned char> & image)
{
	int length = width * height * 4;

	int r, c;
	int i;
	for ( r = 0 ; r < height; r ++)
	{
		for (c = 0; c < width; c++)
		{
			i = r * width * 4 + c * 4;


			Color cur_color(getColorAt(r,c));

			image.at(i) = colorFloat2Byte(cur_color(0));		//r
			image.at(i+1) = colorFloat2Byte(cur_color(1));		//g
			image.at(i+2) = colorFloat2Byte(cur_color(2));		//b
			image.at(i+3) = 255;								//a
		}
	}
}


void Film::outputPNG(const char * filename)
{
	vector<unsigned char> image(width * height * 4);	//RGBA

	//convert image_buckets to image
	generateImgVector(image);


	//Encode the image
	unsigned error = lodepng::encode(filename, image, width, height);

	//if there's an error, display it
	if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}