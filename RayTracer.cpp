#include "RayTracer.h"

#include "Scene.h"


Ray RayTracer::createReflectionRay(LocalGeo & local,Ray & in_ray)
{
	Vector3f n_reflect_dir = local.getReflectDirection(-in_ray.getDirection());

	return Ray(Point(local.pos + MY_EPSILON * n_reflect_dir) ,n_reflect_dir,in_ray.getNI());
}

Ray RayTracer::createRefractionRay(LocalGeo & local,Ray & in_ray,float nt,bool & tir)
{
	//bad trick
	Vector3f in_ray_direction(in_ray.getDirection());
	float c = local.n.dot(-in_ray_direction);
	if(c<0)
	{
		//inside to outside
		nt = 1;

		local.n = Normal(-local.n);
	}


	float nn = in_ray.getNI() / nt;		// ni/nt	
	Vector3f n_refract_dir = local.getRefractionDirection(-in_ray_direction,nn,tir);

	if(!tir)
	{
		return Ray(Point(local.pos + MY_EPSILON * n_refract_dir) ,n_refract_dir, nt);
	}
	else
	{
		return Ray();	//this will not be used
	}
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



		Vector3f view = - ray.getDirection();

		{
			//area light source (shadow ray)
			vector<AreaLight*>& vec_light = scene.getAreaLight();
			vector<AreaLight*>::iterator iter;

			
			for (iter = vec_light.begin();iter != vec_light.end();++iter)
			{
				Color sum_color(0,0,0);
				vector<Ray> vec_ray( (*iter)->generateLightRay(in.local) );

				
				vector<Ray>::iterator it;
				for (it = vec_ray.begin();it != vec_ray.end();++it)
				{
					// Check if the light is blocked or not
					if (!primitive->intersectP(*it))
					{
						//no obstacle block
						
						Color tmp_light_color (  (*iter)->getLightColor(0) );
						sum_color += brdf.shading(in.local, *it, tmp_light_color, view);
					}
					else
					{
						//this light doesn't hit it directly
						//shade ambient only
						Color tmp_light_color( (*iter)->getLightColor(0) );
						sum_color += brdf.shadingOnlyAmbient(tmp_light_color);
					}
				}


				color += sum_color*((*iter)->getRate());
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
				
				
				//Vector3f view = - ray.getDirection();
				Color tmp_light_color( (*iter)->getLightColor(0) );
				color += brdf.shading(in.local, l_ray, tmp_light_color,view );
			}
			else
			{
				//this light doesn't hit it directly
				//shade ambient only
				Color tmp_light_color( (*iter)->getLightColor(0) );
				color += brdf.shadingOnlyAmbient(tmp_light_color);
			}
		}

		





		//mirror reflection
		if(brdf.kr.isPositive())
		{
			/*Ray reflectionRay = createReflectionRay(in.local,ray);
			Color tmp_color;
			trace(scene,reflectionRay,primitive,tmp_color,depth+1);
			color += brdf.kr.componentMulti(tmp_color);*/
			//if( in.local.n.dot(-ray.getDirection()) > 0 )
			//{
				Ray reflectionRay = createReflectionRay(in.local,ray);
				Color tmp_color;
				trace(scene,reflectionRay,primitive,tmp_color,depth+1);
				color += brdf.kr.componentMulti(tmp_color);
			//}
		}



		//refraction
		//TODO
		if(brdf.kt.isPositive())
		{
			bool tir = false;	//total internal reflection
			Ray refractionRay = createRefractionRay(in.local,ray,brdf.ni,tir);

			if(!tir)
			{
				Color tmp_color;
				trace(scene,refractionRay,primitive,tmp_color,depth+1);
				
				color += brdf.kt.componentMulti(tmp_color);
			}
		}
		
}