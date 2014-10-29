#include "Scene.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "Eigen/Geometry"

//#include "Transformation.h"

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
	cout<<"reading input file...\n";

	ifstream in;
	in.open(filename);

	

	if(in.is_open())
	{
		vector<Primitive*> plist;
		Material cur_mat;

		Transform<float,3,Affine> t;
		Transform<float,3,Affine> translate_t;	//for sphere
		Transform<float,3,Affine> scale_t;	//prepare for sphere bounding box

		t = Transform<float,3,Affine>::Identity();
		//translate_t = Transform<float,3,Affine>::Identity();
		//scale_t = Transform<float,3,Affine>::Identity();

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

					//pixel_length = (UR - UL).norm() /243; //tmp
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
					a = Point(t*a.colwise().homogeneous());
					b = Point(t*b.colwise().homogeneous());
					c = Point(t*c.colwise().homogeneous());

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
					//!!!tmp
					
					//point = Point(t*point.colwise().homogeneous());
					//r *= t(0,0);
					
					
					Primitive* p = new GeometricPrimitive (new Sphere(point,r,t),cur_mat);

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
					float x,y,z;
					ss>>x>>y>>z;

					t.translate(Vector3f(x,y,z));

					//!!!can have bug if there's other t between 2 translate
					//translate_t.translate(Vector3f(x,y,z));
				}
				else if(type == "xfr")
				{
					float x,y,z;
					ss>>x>>y>>z;

					Vector3f rotate_axis(x,y,z);
					
					//Affine3f R(  AngleAxisf(rotate_axis.norm()/180*M_PI,rotate_axis.normalized()) );
					//t *= R;
					AngleAxisf ar(rotate_axis.norm()/180*M_PI,rotate_axis.normalized());
					t *= ar;
				}
				else if(type == "xfs")
				{
					float x,y,z;
					ss>>x>>y>>z;

					t.scale(Vector3f(x,y,z));


					//!!!can have bug if there's other t between 2 scale
					//scale_t.scale(Vector3f(x,y,z));
				}
				else if(type == "xfz")
				{
					//identical
					t = Transform<float,3,Affine>::Identity();
					//translate_t = Transform<float,3,Affine>::Identity();
					//scale_t = Transform<float,3,Affine>::Identity();
				}
				else if(type == "obj")
				{
					string objname;
					ss>>objname;

					readObjFile(objname,t,cur_mat,plist);
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


	in.close();

	cout<<"finish reading!\n";
}



void Scene::readObjFile(string & objname, Affine3f & t, Material & mat, vector<Primitive*>& plist)
{
	Affine3f t_normal(t.inverse().matrix().transpose());

	vector<Point> vec_Vert;
	vector<Normal> vec_Nor;

	
	ifstream file;
	file.open(objname);

	if(!file.is_open())
	{
		std::cout << "error: Unable to open Obj file" << std::endl;
	}
	else
	{
		string line;
		while(file.good()) {
			std::vector<std::string> split;
			std::string buf;
			std::getline(file,line);
			std::stringstream ss(line);
			while (ss >> buf) {
				split.push_back(buf);
			}
			if(split.size() == 0) {
				continue;
			}
			if (split[0][0] == '#'){
				continue;
			} 
			else if(split[0] == "g")
			{
				//group...
				continue;
			}
			else if(split[0] == "s")
			{
				//ignore...
				continue;
			}
			else if(split[0] == "mtllib")
			{
				//ignore
				continue;
			}
			else if(split[0] == "usemtl")
			{
				//ignore
				continue;
			}
			else if (split[0] == "v"){
				//vertex

				float x = atof(split[1].c_str());
				float y = atof(split[2].c_str());
				float z = atof(split[3].c_str());

				vec_Vert.push_back(Point(x,y,z));

			} else if (split[0] == "vn"){
				//normal

				float x = atof(split[1].c_str());
				float y = atof(split[2].c_str());
				float z = atof(split[3].c_str());

				vec_Nor.push_back(Normal(x,y,z));
			}
			else if(split[0] == "vt")
			{
				//texture
				//ignore now
			}
			else if (split[0] == "f")
			{
				string s;
				int split_size = split.size();
				int num_v = split_size - 1;
				
				int v[50];
				int vt[50];
				int vn[50];
				vn[1] = -1;
				
				int i;
				for (i = 1;i<split_size;i++)
				{
					std::istringstream ss(split.at(i));
					getline(ss, s, '/');
					v[i] = atoi(s.c_str());
					s="-1";

					getline(ss, s, '/');
					vt[i] = atoi(s.c_str());	//texture
					s="-1";

					getline(ss, s, '/');
					vn[i] = atoi(s.c_str());
					s="-1";
				}


				
				for (i = 3; i <= num_v ;i++)
				{
					Point pa(t * (vec_Vert.at(v[1]-1)).colwise().homogeneous());
					Point pb(t * (vec_Vert.at(v[i-1]-1)).colwise().homogeneous());
					Point pc(t * (vec_Vert.at(v[i]-1)).colwise().homogeneous());

					Primitive* p;

					if(vec_Nor.size() == 0)
					{
						p =  new GeometricPrimitive (new Triangle(pa,pb,pc),mat);
					}
					else if(vn[1] == -1)
					{
						Normal an(t_normal * (vec_Nor.at(v[1]-1)).colwise().homogeneous() );
						Normal bn(t_normal * (vec_Nor.at(v[i-1]-1)).colwise().homogeneous() );
						Normal cn(t_normal * (vec_Nor.at(v[i]-1)).colwise().homogeneous() );
						
						p =  new GeometricPrimitive (new Triangle(pa,pb,pc,an,bn,cn),mat);
					}
					else
					{
						Normal an(t_normal * (vec_Nor.at(vn[1]-1)).colwise().homogeneous() );
						Normal bn(t_normal * (vec_Nor.at(vn[i-1]-1)).colwise().homogeneous() );
						Normal cn(t_normal * (vec_Nor.at(vn[i]-1)).colwise().homogeneous() );
						
						p =  new GeometricPrimitive (new Triangle(pa,pb,pc,an,bn,cn),mat);
					}
					plist.push_back(p);
				}
				






				////this version support triangles only
				//string s;
				//std::istringstream ss1(split[1]);
				//getline(ss1, s, '/');
				//int v1 = atoi(s.c_str());
				//getline(ss1, s, '/');
				//int vt1 = atoi(s.c_str());	//texture
				//getline(ss1, s, '/');
				//int vn1 = atoi(s.c_str());

				//std::istringstream ss2(split[2]);
				//getline(ss2, s, '/');
				//int v2 = atoi(s.c_str());
				//getline(ss2, s, '/');
				//int vt2 = atoi(s.c_str());	//texture
				//getline(ss2, s, '/');
				//int vn2 = atoi(s.c_str());

				//std::istringstream ss3(split[3]);
				//getline(ss3, s, '/');
				//int v3 = atoi(s.c_str());
				//getline(ss3, s, '/');
				//int vt3 = atoi(s.c_str());	//texture
				//getline(ss3, s, '/');
				//int vn3 = atoi(s.c_str());



				////TODO transformation
				//Point pa(t * (vec_Vert.at(v1-1)).colwise().homogeneous());
				//Point pb(t * (vec_Vert.at(v2-1)).colwise().homogeneous());
				//Point pc(t * (vec_Vert.at(v3-1)).colwise().homogeneous());

				//Primitive* p;
				//if(vn1 == -1)
				//{
				//	//no normal vector defined for each vertex
				//	//p = new GeometricPrimitive (new Triangle(pa,pb,pc),mat);


				//	
				//	Normal an(t_normal * (vec_Nor.at(v1-1)).colwise().homogeneous() );
				//	Normal bn(t_normal * (vec_Nor.at(v2-1)).colwise().homogeneous() );
				//	Normal cn(t_normal * (vec_Nor.at(v3-1)).colwise().homogeneous() );

				//	p =  new GeometricPrimitive (new Triangle(pa,pb,pc,an,bn,cn),mat);
				//}
				//else
				//{
				//	Normal an(t_normal * (vec_Nor.at(vn1-1)).colwise().homogeneous() );
				//	Normal bn(t_normal * (vec_Nor.at(vn2-1)).colwise().homogeneous() );
				//	Normal cn(t_normal * (vec_Nor.at(vn3-1)).colwise().homogeneous() );
				//	p = new GeometricPrimitive (new Triangle(pa,pb,pc,an,bn,cn),mat);
				//}
				//plist.push_back(p);

			}
			else
			{
				cout<<"Warning! undefined label!\n";
				abort();
			}




		}
	}


	file.close();
}