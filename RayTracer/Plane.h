#pragma once

#include "Object.h"
//!Flat Plane object
class Plane : public Object
{
public:
	Intersection RayInterect(Ray _ray);	//!< Plane intersection
	//void SetNormal(glm::vec3 _intersectPoint) {  surfaceNormal = -(glm::normalize(position)); }	//!< Sets Plane Normal
	glm::vec3 GetNormal(glm::vec3 _intersectPoint) { return -(glm::normalize(position)); }//!< Gets Plane Normal
};