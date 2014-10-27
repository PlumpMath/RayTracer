#include "BoundingBox.h"


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
	return (min_pos + 0.5*length);
}
