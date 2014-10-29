#include "BoundingBox.h"


BoundingBox::BoundingBox(const Point & pmin,const Point & pmax, const Affine3f & t)
{
	Vector3f offset(pmin - pmax);
	Vector3f offset_x(offset(0),0,0);
	Vector3f offset_y(0,offset(1),0);
	Vector3f offset_z(0,0,offset(2));
	Vector3f v[8];

	v[0] = pmin;

	v[1] = pmin + offset_x;
	v[2] = pmin + offset_y;
	v[3] = pmin + offset_z;
	
	v[4] = pmax - offset_x;
	v[5] = pmax - offset_y;
	v[6] = pmax - offset_z;

	v[7] = pmax;

	int i;
	for (i =0;i<8;i++)
	{
		v[i] = t * (v[i].colwise().homogeneous());
	}

	float min_x = (v[0]).x();
	float min_y = (v[0]).y();
	float min_z = (v[0]).z();

	float max_x = (v[0]).x();
	float max_y = (v[0]).y();
	float max_z = (v[0]).z();

	for (i =1;i<8;i++)
	{
		min_x = min(min_x,(v[i]).x());
		min_y = min(min_y,(v[i]).y());
		min_z = min(min_z,(v[i]).z());

		max_x = max(max_x,(v[i]).x());
		max_y = max(max_y,(v[i]).y());
		max_z = max(max_z,(v[i]).z());
	}

	min_pos = Point(min_x,min_y,min_z);
	max_pos = Point(max_x,max_y,max_z);
}




bool BoundingBox::IntersectP(const Ray & ray)
{
	//shadow ray and reflected ray returns false mistakenly
	//probably because they are in the box


	Vector3f pos(ray.getStartPosition());
	Vector3f inv_dir(ray.getInvDirection());


	float tx1 = (min_pos.x() - pos.x())*inv_dir.x();
	float tx2 = (max_pos.x() - pos.x())*inv_dir.x();

	float tmin = min(tx1, tx2);
	float tmax = max(tx1, tx2);

	float ty1 = (min_pos.y() - pos.y())*inv_dir.y();
	float ty2 = (max_pos.y() - pos.y())*inv_dir.y();

	tmin = max(tmin, min(ty1, ty2));
	tmax = min(tmax, max(ty1, ty2));


	//TODO, t should >0

	if (tmax >= tmin)
	{
		float tz1 = (min_pos.z() - pos.z())*inv_dir.z();
		float tz2 = (max_pos.z() - pos.z())*inv_dir.z();

		tmin = max(tmin, min(tz1, tz2));
		tmax = min(tmax, max(tz1, tz2));


		//To confirm?? tmax>0
		if(tmax >= tmin && tmax > 0)
		{
			//the line of ray will intersect
			//but maybe the t < 0

			

			return true;
		}
	}



	return false;






	
	//Vector3f dir(ray.getDirection());
	//Vector3f inv_dir(ray.getInvDirection());


	//float tx1 = (min_pos.x() - dir.x())*inv_dir.x();
	//float tx2 = (max_pos.x() - dir.x())*inv_dir.x();

	//float tmin = min(tx1, tx2);
	//float tmax = max(tx1, tx2);

	//float ty1 = (min_pos.y() - dir.y())*inv_dir.y();
	//float ty2 = (max_pos.y() - dir.y())*inv_dir.y();

	//tmin = max(tmin, min(ty1, ty2));
	//tmax = min(tmax, max(ty1, ty2));


	////TODO, t should >0

	//if (tmax >= tmin)
	//{
	//	float tz1 = (min_pos.z() - dir.z())*inv_dir.z();
	//	float tz2 = (max_pos.z() - dir.z())*inv_dir.z();

	//	tmin = max(tmin, min(tz1, tz2));
	//	tmax = min(tmax, max(tz1, tz2));


	//	if(tmax >= tmin)
	//	{
	//		//the line of ray will intersect
	//		//but maybe the t < 0

	//		//TODO
	//		return true;
	//	}
	//}



	//return false;



}


Vector3f BoundingBox::getMidPoint()
{
	//return (min_pos + 0.5*length);
	return ((min_pos + max_pos)/2);
}
