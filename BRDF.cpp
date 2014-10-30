#include "BRDF.h"



BRDF::BRDF()
	:shiniess(0)
	,ni(1.0)
{
}

BRDF::BRDF(const Color & a,const Color & d,const Color & s,float v,const Color & r,const Color & t,float nnn  )
	:ka(a),kd(d),ks(s),shiniess(v),kr(r)
	,kt(t)
	,ni(nnn)
{
}



Color BRDF::shadingOnlyAmbient(Color& light_color)
{
	Color color;
	//ambient
	color += ka.componentMulti(light_color);

	return color;
}


Color BRDF::shading(LocalGeo & local, Ray & light_ray, Color& light_color,Vector3f & view)
{
	//light_ray is pointing from local to light

	Color color;

	//ambient
	color += ka.componentMulti(light_color);

	//diffuse
	float tmp1_cos = (light_ray.getDirection()).dot(local.n);
	color += kd.componentMulti(  (Color)( light_color * ((tmp1_cos > 0) ? tmp1_cos : 0.0) ) );

	//specular
	//Is = ks.componentMultiply(  light.color * ( pow( max(n_view.dot(n_reflect),0) , p ) ) );
	//how to get view?
	Vector3f n_reflect_dir = local.getReflectDirection(light_ray.getDirection());
	float tmp2_cos = view.dot(n_reflect_dir);
	color += ks.componentMulti( (Color) (light_color * pow( (tmp2_cos>0) ? tmp2_cos : 0 ,shiniess)  ) );


	return color;
}
