#include "Scene.h"


Scene::Scene(const Camera & c, const Sampler & s, const RayTracer & r, const Film & f, Primitive * p)
	:camera(c), sampler(s), rayTracer(r), film(f)
{
	primitive = p;
}



void Scene::render(const char * filename)
{
	Vector3f * sample_pos = NULL;
	
	


	//bool is_sample_end = ! sampler.getSample(sample_pos);

	int row, column;
	while (sampler.getSample(sample_pos, row, column))
	{
		//getSample::sample_pos has released
		Color color;
		Ray * ray = & camera.generateRay(*sample_pos);	//?
		rayTracer.trace(*ray, primitive,color,0);

		film.commit(row,column,color);

	}


	film.outputPNG(filename);


	delete sample_pos;
	//delete ray;
}