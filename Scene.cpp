#include "Scene.h"

#include <iostream>
#include <fstream>
#include <sstream>



#include "Transformation.h"

#include "PointLight.h"
#include "DirectionalLight.h"
#include "AmbientLight.h"

#include "Material.h"
#include "GeometricPrimitive.h"
#include "Sphere.h"
#include "Triangle.h"
#include "AggregatePrimitiveKDNode.h"



using namespace std;

Scene::Scene(string & filename)
{
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//tmp
	pixel_length = 100.0 / 1000.0;	//tmp

	readFile(filename);
}



Scene::Scene(const Camera & c, const Sampler & s, const RayTracer & r, const Film & f, Primitive * p)
	:camera(c), sampler(s), rayTracer(r), film(f)
{
	primitive = p;
}

Scene::~Scene()
{
	delete primitive;

	{
		vector<Light*>::iterator iter;

		for (iter = vec_light.begin();iter != vec_light.end();++iter)
		{
			if( (*iter) != NULL)
			{
				delete (*iter);
				(*iter) = NULL;
			}
		}
	}


	{
		vector<AmbientLight*>::iterator iter;

		for (iter = vec_ambient_light.begin();iter != vec_ambient_light.end();++iter)
		{
			if( (*iter) != NULL)
			{
				delete (*iter);
				(*iter) = NULL;
			}
		}
	}
}


void Scene::addLight(Light * light)
{
	vec_light.push_back(light);
}

void Scene::addAmbientLight(AmbientLight * al)
{
	vec_ambient_light.push_back(al);
}


//void Scene::LoopLight(LocalGeo& local)
//{
//	vector<Light*>::iterator iter;
//
//	for (iter = vec_light.begin();iter != vec_light.end();++iter)
//	{
//		Ray ray(;
//		(*iter)->generateLightRay(in.local, &lray, &lcolor);
//
//		// Check if the light is blocked or not
//		if (!primitive->intersectP(lray))
//			*color += shading(in.local, brdf, lray, lcolor);
//	}
//}

//Vector3f Scene::getViewVector(LocalGeo& local)
//{
//	return (camera.pos - local.pos).normalized();
//}



void Scene::render(const char * filename)
{
	//Vector3f * sample_pos = NULL;
	Vector3f sample_pos;
	
	//bool is_sample_end = ! sampler.getSample(sample_pos);

	int row, column;
	while (sampler.getSample(sample_pos, row, column))
	{
		//getSample::sample_pos has released
		Color color;
		Ray ray ( camera.generateRay(sample_pos) );	//?
		
		rayTracer.trace(*this, ray, primitive,color,0);

		film.commit(row,column,color);

	}


	film.outputPNG(filename);


	//delete sample_pos;
	//delete ray;
}








void Scene::readFile(string & filename)
{
	ifstream in;
	in.open(filename);

	

	if(in.is_open())
	{
		vector<Primitive*> plist;
		Material cur_mat;




		string line;
		while(getline(in,line))
		{
			if(line != "")
			{
				stringstream ss(line);

				string type;
				ss>>type;

				if(type == "#")
				{
					//comment

				}
				else if(type == "cam")
				{
					//camera
					float ex, ey, ez, llx, lly, llz, lrx, lry, lrz, ulx, uly, ulz, urx, ury, urz;
					ss >> ex>> ey>> ez>> llx>> lly>> llz>> lrx>> lry>> lrz>> ulx>> uly>> ulz>> urx>> ury>> urz;

					camera = Camera(ex,ey,ez);
					Vector3f UL(ulx,  uly, ulz);
					Vector3f UR( urx,  ury, urz);
					Vector3f LR( lrx, lry, lrz);
					Vector3f LL( llx, lly, llz);


					sampler = Sampler(UL,UR,LR,LL,pixel_length);
					film = Film(sampler.getWidth(),sampler.getHeight());
				}
				else if (type == "tri")
				{
					float x1, y1, z1, x2, y2, z2, x3, y3, z3;	//triangle
					ss>>x1>>y1>>z1>>x2>> y2>> z2>> x3>> y3>> z3;

					Point a(x1,y1,z1);
					Point b(x2,y2,z2);
					Point c(x3,y3,z3);

					//TODO transformation


					Primitive* p = new GeometricPrimitive (new Triangle(a,b,c),cur_mat);
					plist.push_back(p);
				}
				else if(type == "sph")
				{
					//sphere
					float cx, cy, cz, r;
					ss>>cx>>cy>>cz>>r;
					
					Point point(cx,cy,cz);

					//TODO transformation

					Primitive* p = new GeometricPrimitive (new Sphere(point,r),cur_mat);

					plist.push_back(p);
				}
				else if(type == "ltp")
				{
					//point light
					float px, py, pz, pr, pg, pb;	// point lights
					int falloff = 0;
					ss>>px>>py>>pz>>pr>>pg>>pb;	
					//[falloff]
					ss>>falloff;


					addLight(new PointLight(Vector3f(px,py,pz),Color(pr,pg,pb),falloff));
				}
				else if(type == "ltd")
				{
					float dx, dy, dz, dr, dg, db;
					ss>>dx>>dy>>dz>>dr>>dg>>db;

					addLight(new DirectionalLight(Vector3f(dx,dy,dz),Color(dr,dg,db)));
				}
				else if(type == "lta")
				{
					float ar, ag, ab;	//ambient
					ss>>ar>>ag>>ab;

					addAmbientLight(new AmbientLight(Color(ar,ag,ab)));
				}
				else if(type == "mat")
				{
					float kar, kag, kab, kdr, kdg, kdb, ksr, ksg, ksb, ksp, krr, krg, krb;	//material
					ss>> kar>> kag>> kab>> kdr>> kdg>> kdb
						>> ksr>> ksg>> ksb>> ksp
						>> krr>> krg>> krb;

					cur_mat = Material (BRDF(Color(kar,kag,kab)
						,Color(kdr,kdg,kdb)
						,Color(ksr,ksg,ksb),ksp
						,Color(krr,krg,krb)));
				}
				else if(type == "xft")
				{
					
				}
				else if(type == "xfr")
				{
					
				}
				else if(type == "xfs")
				{
					
				}
				else if(type == "xfz")
				{
					//identical
				}
				else if(type == "obj")
				{
					
				}
				else
				{
					//warning
					cout<<"Warning: Undefined Type!\n";
				}


			}
		}





		primitive = new AggregatePrimitiveKDNode(plist,0);
	}
	else
	{
		//fail to open file
	}


}