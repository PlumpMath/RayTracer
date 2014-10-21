#pragma once

#include "Eigen/Dense"

#include "Camera.h"
#include "Sampler.h"
#include "RayTracer.h"
#include "Film.h"

#include "Primitive.h"


using namespace Eigen;
using namespace std;


class Scene
{
protected:
	Camera camera;
	Sampler sampler;
	RayTracer rayTracer;
	Film film;


	Primitive * primitive;

public:
	//Scene(const Camera & c, const Sampler & s, const RayTracer & r, const Film & f, Primitive * p);
	Scene(const Camera & c, const Sampler & s, const RayTracer & r, const Film & f, Primitive * p);

	void render(const char * filename);
};