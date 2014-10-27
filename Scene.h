#pragma once

#include <vector>
#include <string>


#include "Eigen/Dense"


#include "Light.h"
#include "AmbientLight.h"

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
	vector<AmbientLight*> vec_ambient_light;

	Primitive * primitive;

	float pixel_length;
public:
	//Scene(const Camera & c, const Sampler & s, const RayTracer & r, const Film & f, Primitive * p);
	Scene(string & filename);
	Scene(const Camera & c, const Sampler & s, const RayTracer & r, const Film & f, Primitive * p);
	~Scene();


	void addLight(Light * light);
	void addAmbientLight(AmbientLight * al);
	

	//Vector3f getViewVector(LocalGeo & local);

	vector<Light*>& getVecLight(){return vec_light;}
	vector<AmbientLight*>& getAmbientLight(){return vec_ambient_light;}
	//void LoopLight(LocalGeo& local);

	void render(const char * filename);



	void readFile(string & filename);
};