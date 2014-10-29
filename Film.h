#pragma once

#include "Eigen/Dense"

#include "Color.h"

#include <vector>

using namespace std;

class Film
{
protected:
	int width;
	int height;

	//color of each pixel (buckets)
	//TODO

	//test, one sample for each pixel
	//vector < vector<Color> > image_bucket;


	vector < vector< vector<Color> > > image_bucket;

public:
	Film(int w = 100,int h = 60);

	unsigned char colorFloat2Byte(float c)
	{
		float tmp = c *255;
		tmp = (tmp>255) ? 255 : tmp;
		return (unsigned char)tmp;
	}

	Color getColorAt(int row, int column);

	void commit(int row, int column, Color & color);

	void generateImgVector(vector<unsigned char> & image);

	void outputPNG(const char * filename);
};