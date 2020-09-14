#include "Sphere.h"
#include "Ray.h"


Intersection Sphere::RayInterect(Ray _ray)
{
	Intersection result;

	//Calculating the Sphere
	//a = origin of ray 
	//n = direction of ray
	//P = center of sphere (position in object)
	//r = radius of sphere (radius)

	//d = distance from the center of the sphere to the closest point of the ray to the center of the sphere
	//x = distance from (the closest point on the line to the center point of the sphere) to (the intersection point) 
	// small . before n is dot product (glm::dot)

	float distanceToIntersect = glm::dot(position - _ray.origin, _ray.direction);
	float distance = glm::length(position - _ray.origin - (distanceToIntersect) * _ray.direction);

	if (distance > radius)
	{
		return result;
	}
	if (distanceToIntersect < 0)	
	{
		return result;
	}
	result.hit = true;
	float x =  glm::sqrt(glm::pow(radius, 2) - glm::pow(distance, 2));
	//result.distanceToIntersect = glm::dot(position - _ray.origin, _ray.direction) - x;
	result.distanceToIntersect = distanceToIntersect - x;
	result.intersectPoint = _ray.origin + (((distanceToIntersect - x) * _ray.direction));
	//result.intersectPoint = _ray.origin + (((glm::dot(position - _ray.origin, _ray.direction) - x) * _ray.direction));

	return result;
}
