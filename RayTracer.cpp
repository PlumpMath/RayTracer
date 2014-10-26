#include "RayTracer.h"

#include "Scene.h"


Ray RayTracer::createReflectRay(LocalGeo & local,Ray & in_ray)
{
	Vector3f n_reflect_dir = local.getReflectDirection(-in_ray.getDirection());

	return Ray(Point(local.pos + 0.0001 * n_reflect_dir) ,n_reflect_dir);
}




void RayTracer::trace(Scene & scene, Ray & ray, Primitive * primitive, Color & color, int depth)
{
		if (depth >= depth_max)
		{
			//color += Color(0.0, 0.0, 0.0);
			return;
		}

		float t_hit;
		Intersection in;
		if(!primitive->intersect(ray,t_hit,in))
		{
			//no hit
			//color += Color(0.0, 0.0, 0.0);
			return;
		}


		//There's a hit
		//test
		//color.set(0,1,0);

		BRDF brdf;
		in.getBRDF(brdf);


		{
			//ambient light source
			vector<AmbientLight*>& vec_ambient_light = scene.getAmbientLight();
			vector<AmbientLight*>::iterator iter;
			for(iter = vec_ambient_light.begin();iter != vec_ambient_light.end(); ++iter)
			{
				color += brdf.shadingOnlyAmbient((*iter)->intensity);
			}
		}



		//loop through all light source (shoot shadow rays)
		vector<Light*>& vec_light = scene.getVecLight();

		vector<Light*>::iterator iter;

		for (iter = vec_light.begin();iter != vec_light.end();++iter)
		{
			Ray l_ray ( (*iter)->generateLightRay(in.local) );
			

			// Check if the light is blocked or not
			if (!primitive->intersectP(l_ray))
			{
				//no obstacle block
				//TODO,need to ask scene for camera position
				
				//TODO the view has some problem
				//Vector3f view = scene.getViewVector(in.local);
				Vector3f view = - ray.getDirection();
				Color& tmp_light_color = (*iter)->getLightColor(0);
				color += brdf.shading(in.local, l_ray, tmp_light_color,view );
			}
			else
			{
				//this light doesn't hit it directly
				//shade ambient only
				Color& tmp_light_color = (*iter)->getLightColor(0);
				color += brdf.shadingOnlyAmbient(tmp_light_color);
			}
		}

		





		//mirror reflection
		if(brdf.kr.isPositive())
		{
			Ray reflectRay = createReflectRay(in.local,ray);


			Color tmp_color;
			trace(scene,reflectRay,primitive,tmp_color,depth+1);
			color += brdf.kr.componentMulti(tmp_color);
		}
		
}