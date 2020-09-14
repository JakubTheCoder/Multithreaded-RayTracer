#include "Plane.h"
#include "Ray.h"

Intersection Plane::RayInterect(Ray _ray)
{
	Intersection result;
	glm::vec3 surfaceNormal = -(glm::normalize(position));

	//Calculating Plane intersection
	//t = distance from origin to intersection point;
	//po = position
	//normal goes from the point
	//p = intersection point 
	//a = ray origin
	//n = ray direction

	float distanceToIntersect = glm::dot((position - _ray.origin), surfaceNormal) / glm::dot(_ray.direction, surfaceNormal);

	glm::vec3 intersectPoint = _ray.origin + distanceToIntersect * _ray.direction;
	if (distanceToIntersect > 0)
	{
		result.hit = true;
		result.distanceToIntersect = distanceToIntersect;
		result.intersectPoint = intersectPoint;
	}

	return result;
}