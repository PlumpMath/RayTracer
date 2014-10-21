#include <iostream>


#include "Eigen/Dense"

#include "Sphere.h"
#include "GeometricPrimitive.h"
#include "Scene.h"



using namespace Eigen;
using namespace std;


int main(int argc, char * argv[])
{
	//temp test

	
	Camera camera(Vector3f(0,0,0));
	Vector3f UL(-1,  1, -1);
	Vector3f UR( 1,  1, -1);
	Vector3f LR( 1, -1, -1);
	Vector3f LL(-1, -1, -1);
	
	/*
	Camera camera(Vector3f(0,0,0));
	Vector3f UL(-1,  1, 0);
	Vector3f UR( 1,  1, -2);
	Vector3f LR( 1, -1, -2);
	Vector3f LL(-1, -1, 0);
	*/

	Sampler sampler(UL,UR,LR,LL,0.02);

	RayTracer rayTracer;
	Film film(sampler.getWidth(),sampler.getHeight());

	//temp
	GeometricPrimitive primitive(new Sphere(Point(0.6,-0.2,-2.5),1));
	//GeometricPrimitive primitive(new Sphere(Point(0,0,-2),1));

	Scene scene(camera,sampler,rayTracer,film,&primitive);

	scene.render("test.png");



}