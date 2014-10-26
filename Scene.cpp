#include "Scene.h"


Scene::Scene(const Camera & c, const Sampler & s, const RayTracer & r, const Film & f, Primitive * p)
	:camera(c), sampler(s), rayTracer(r), film(f)
{
	primitive = p;
}

Scene::~Scene()
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


void Scene::addLight(Light * light)
{
	vec_light.push_back(light);
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