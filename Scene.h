#pragma once

#include <vector>


#include "Eigen/Dense"


#include "Light.h"
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

	vector<Light*> vec_light;

	Primitive * primitive;

public:
	//Scene(const Camera & c, const Sampler & s, const RayTracer & r, const Film & f, Primitive * p);
	Scene(const Camera & c, const Sampler & s, const RayTracer & r, const Film & f, Primitive * p);
	~Scene();


	void addLight(Light * light);

	Vector3f getViewVector(LocalGeo & local);

	vector<Light*>& getVecLight(){return vec_light;}
	//void LoopLight(LocalGeo& local);

	void render(const char * filename);
};