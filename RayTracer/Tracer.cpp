#include <algorithm>
#include "Tracer.h"

#include "Ray.h"

glm::vec3 Tracer::TraceRay(Ray _ray, int _traceBounce)
{
	if (_traceBounce > traceLimit)	//Limits the amounts of Ray bounces
	{
		return glm::vec3{ 0.0f };
	}

	float closestPoint = INFINITY;	//Closest intersection point on the ray, set to highest possible value 
	Intersection res;	//result of intersection
	Object* temp = NULL;	//temp object that will be drawn
	glm::vec3 colour{ 0.0f };	//colour

	for (int i = 0; i < objects.size(); i++)	//Go through all objects
	{
		Intersection tempRes = objects.at(i)->RayInterect(_ray);	//Temp result so it doesn't get overriden by closest point 

		//checks if ray was hit and checks to see if currect hit ray is the closest surface
		if (tempRes.hit == true && tempRes.distanceToIntersect<closestPoint)	
		{
			temp = objects.at(i);	//set temp object to closest object
			closestPoint = tempRes.distanceToIntersect;	//set closest point to the new closest point
			res = tempRes;	//set temp result to the actual results
		}

	}
	
	if (temp)	//if there is a object that is was hit by a ray, draw it 
	{
		colour = temp->Shade(_ray,*this,res.intersectPoint, _traceBounce);
	}
	return colour;
}

bool Tracer::ShadowRay(Ray _shadow)
{
	//this trace function only needs to check if there is a object in the way, not the distance
	for (int i = 0; i < objects.size(); i++)
	{
		Intersection tempRes = objects.at(i)->RayInterect(_shadow);

		if (tempRes.hit == true )
		{
			return true;
		}

	}
	return false;
}