#include <iostream>


#include "Eigen/Dense"


#include "PointLight.h"
#include "DirectionalLight.h"
#include "Sphere.h"
#include "Triangle.h"
#include "GeometricPrimitive.h"
#include "AggregatePrimitive.h"
#include "Scene.h"



using namespace Eigen;
using namespace std;


int main(int argc, char * argv[])
{
	//temp test

	
	Camera camera(Vector3f(0,0,0));
	Vector3f UL(-1,  1, -3);
	Vector3f UR( 1,  1, -3);
	Vector3f LR( 1, -1, -3);
	Vector3f LL(-1, -1, -3);
	
	

	//float pixel_length = 0.02;
	float pixel_length = 2.0 / 500.0;
	Sampler sampler(UL,UR,LR,LL,pixel_length);

	RayTracer rayTracer;
	Film film(sampler.getWidth(),sampler.getHeight());
	
	vector<Primitive*> vec_primitive;




	////my test scene
	//Material mat1(BRDF(Color(0.1,0,0),Color(0.6,0,0),Color(1,1,1),16,Color(0.8,0.8,0.8)));
	//vec_primitive.push_back(new GeometricPrimitive (new Sphere(Point(1,-2,-7),1.5),mat1) );
	//
	//
	//Material mat2(BRDF(Color(0.1,0.1,0),Color(0.7,0.7,0),Color(1,1,0),16,Color(0.8,0.8,0.8)));
	//vec_primitive.push_back(new GeometricPrimitive (new Sphere(Point(-2,2,-4.5),0.5),mat2) );
	//

	//Material mat3(BRDF(Color(0,0,0.1),Color(0,0,0.7),Color(0,0,1),16,Color(0.8,0.8,0.8)));
	//vec_primitive.push_back(new GeometricPrimitive (
	//	new Triangle(Point(-5,-5,-10),Point(12,2,-13),Point(0,10,-16))
	//	,mat3 ) );
	////////////////



	//guide test scene
	Material mat1(BRDF(Color(0.1,0.1,0.1),Color(1,0,1),Color(1,1,1),50,Color(0,0,0)));
	vec_primitive.push_back(new GeometricPrimitive (new Sphere(Point(0,0,-20),3.0),mat1) );

	Material mat2(BRDF(Color(0.1,0.1,0.1),Color(1,1,0),Color(1,1,1),50,Color(0,0,0)));
	vec_primitive.push_back(new GeometricPrimitive (new Sphere(Point(-2,2,-15),1.0),mat2) );

	Material mat3(BRDF(Color(0.1,0.1,0.1),Color(0,1,1),Color(1,1,1),50,Color(0,0,0)));
	vec_primitive.push_back(new GeometricPrimitive (new Sphere(Point(-2,-2,-15),1.0),mat3) );

	Material mat4(BRDF(Color(0.1,0.1,0.1),Color(0.1,0.1,0.1),Color(1,1,1),50.,Color(1,1,1)));
	vec_primitive.push_back(new GeometricPrimitive (
		new Triangle(Point(5,5,-17),Point(1,4,-20),Point(6,-1,-20))
		,mat4 ) );
	//////////////////////


	AggregatePrimitive primitive(vec_primitive);



	Scene scene(camera,sampler,rayTracer,film,&primitive);

	//addlight
	scene.addLight(new DirectionalLight(Vector3f(0.57735027,-0.57735027,-0.57735027),Color(1,1,1)));
	scene.addLight(new DirectionalLight(Vector3f(0.57735027,0.57735027,-0.57735027),Color(0,0,1)));


	scene.render("test.png");



}