#include "Film.h"

#include "loadpng/lodepng.h"
#include <iostream>

Film::Film(int w,int h)
		:image_bucket(h,vector<Color>(w))
		,width(w)
		,height(h)
{
}



unsigned char Film::getColorAt(int row, int column,int i)
{
	//test: one sample for one pixel

	return colorFloat2Byte( (image_bucket.at(row).at(column))(i) );
}



void Film::commit(int row, int column, Color & color)
{
	//test
	image_bucket.at(row).at(column).set(color);
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

			image.at(i) = getColorAt(r,c,0);		//r
			image.at(i+1) = getColorAt(r,c,1);		//g
			image.at(i+2) = getColorAt(r,c,2);		//b
			image.at(i+3) = 255;					//a
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