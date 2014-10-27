#include <iostream>
#include "AggregatePrimitiveKDNode.h"

//AggregatePrimitiveKDNode::AggregatePrimitiveKDNode()
//{
//	left = NULL;
//	right = NULL;
//}


AggregatePrimitiveKDNode::AggregatePrimitiveKDNode(vector<Primitive*> & list,int depth)
	//:vec_primitive(list)
{
	//the list is actually a GeometricPrimitive list

	int num_primitives = list.size();

	if(num_primitives == 0)
	{
		cout<<"error: a null aggregate primitive kd node shouldn't be generated!\n";
		abort();
	}
	else if(num_primitives <= THREDSHOLD_NUM_PRIMITIVES)
	{
		//??
		vec_primitive = list;
		initBoundingBox();
		return;
	}
	else
	{
		//
		Vector3f mid_point;
		vector<Primitive*> vec_left;
		vector<Primitive*> vec_right;

		//TODO, split space

		//1.get avg point
		Vector3f avg_point(0.0,0.0,0.0);
		vector<Primitive*>::iterator iter;
		for (iter = list.begin(); iter != list.end() ; ++iter)
		{
			BoundingBox& bb = (*iter)->getBoundingBox();
			avg_point += bb.getMidPoint();
		}
		avg_point /= num_primitives;

		//2.choose split axis
		//by depth now
		//0-x,1-y,2-z
		int axis = depth;

		//3.split
		for (iter = list.begin(); iter != list.end() ; ++iter)
		{
			BoundingBox& bb = (*iter)->getBoundingBox();
			
			Vector3f cur_mid_point(bb.getMidPoint());
			if(cur_mid_point(axis) < avg_point(axis))
			{
				vec_left.push_back(*iter);
			}
			else
			{
				vec_right.push_back(*iter);
			}
		}



		if(vec_left.size() > 0)
		{
			Primitive* pleft = new AggregatePrimitiveKDNode(vec_left,(depth+1)%3);
			vec_primitive.push_back(pleft);
		}


		if(vec_right.size() > 0)
		{
			Primitive* pright = new AggregatePrimitiveKDNode(vec_right,(depth+1)%3);
			vec_primitive.push_back(pright);
		}

		initBoundingBox();
	}
}






AggregatePrimitiveKDNode::~AggregatePrimitiveKDNode()
{
	vector<Primitive*>::iterator iter;
	for (iter = vec_primitive.begin(); iter != vec_primitive.end() ; ++iter)
	{
		if((*iter) != NULL)
		{
			delete (*iter);
			(*iter) = NULL;
		}
	}
}


bool AggregatePrimitiveKDNode::intersect(Ray& ray, float& t_hit, Intersection & in)
{
	bool is_hit = false;
	t_hit = MY_FLOAT_MAX;


	

	if(boundingBox.IntersectP(ray))
	{
		vector<Primitive*>::iterator iter;
		for (iter = vec_primitive.begin();iter != vec_primitive.end(); ++iter)
		{
			float this_t;
			Intersection this_in;
			bool is_this_hit = (*iter)->intersect(ray,this_t,this_in);

			
			is_hit = is_hit || is_this_hit;

			if(is_this_hit && this_t < t_hit)
			{
				t_hit = this_t;
				in = this_in;
				//in.primitive = (*iter);
			}
			
			
		}
	}


	

	return is_hit;
}


bool AggregatePrimitiveKDNode::intersectP(Ray& ray)
{
	bool is_hit = false;

	//test
	//float test_x = ray.getStartPosition().x();

	if(boundingBox.IntersectP(ray))
	{
		vector<Primitive*>::iterator iter;
		for (iter = vec_primitive.begin();iter != vec_primitive.end(); ++iter)
		{
			is_hit = (*iter)->intersectP(ray);

			//will get here only when hit a geometric primitive

			if (is_hit)
			{
				return true;
			}
		}
	}
	return is_hit;
}


void AggregatePrimitiveKDNode::getBRDF(LocalGeo& local, BRDF& brdf)
{
	// This should never get called, because in->primitive will
	// never be an aggregate primitive
	cout<<"error: AggregatePrimitiveKDNode getBRDF shouldn't be called ever\n";
	abort();
}



void AggregatePrimitiveKDNode::initBoundingBox()
{
	//TODO
	int num_primitives = vec_primitive.size();

	if(num_primitives == 0)
	{
		//something is wrong
		cout<<"error:AggregatePrimitive KDNode with 0 primitives in the vector!\n";
		abort();
	}

	/*if(num_primitives == 1)
	{
		Primitive* p = vec_primitive.at(0);
		boundingBox =  (p->getBoundingBox());
		return;
	}*/



	//num_primitives > 0
	
	float min_pos_x = MY_FLOAT_MAX;
	float min_pos_y = MY_FLOAT_MAX;
	float min_pos_z = MY_FLOAT_MAX;

	float max_pos_x = MY_FLOAT_MIN;
	float max_pos_y = MY_FLOAT_MIN;
	float max_pos_z = MY_FLOAT_MIN;
	vector<Primitive*>::iterator iter;
	for(iter = vec_primitive.begin();iter != vec_primitive.end();++iter)
	{
		BoundingBox box((*iter)->getBoundingBox());

		min_pos_x = min(min_pos_x,box.min_pos(0));
		min_pos_y = min(min_pos_y,box.min_pos(1));
		min_pos_z = min(min_pos_z,box.min_pos(2));

		max_pos_x = max(max_pos_x,box.max_pos(0));
		max_pos_y = max(max_pos_y,box.max_pos(1));
		max_pos_z = max(max_pos_z,box.max_pos(2));
	}
	Point min_pos(min_pos_x,min_pos_y,min_pos_z);
	Point max_pos(max_pos_x,max_pos_y,max_pos_z);

	boundingBox = BoundingBox(min_pos,max_pos);
}



BoundingBox& AggregatePrimitiveKDNode::getBoundingBox()
{
	return boundingBox;
}

