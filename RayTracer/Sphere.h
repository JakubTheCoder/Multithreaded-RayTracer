#pragma once

#include "Object.h"
//!Sphere object class
class Sphere :public Object
{
public:
	Intersection RayInterect(Ray _ray); //!< Sphere Ray Intersection
	void SetRadius(float _rad) { radius = _rad; }	//!< Set Radius
	//void SetNormal(glm::vec3 _intersectPoint) {  surfaceNormal = glm::normalize(_intersectPoint - position);}	//!<Set Surface Normal
	glm::vec3 GetNormal(glm::vec3 _intersecPoint) { return glm::normalize(_intersecPoint - position); }	//!< Get Surface Normal

private:
	float radius;	//Sphere radius
};