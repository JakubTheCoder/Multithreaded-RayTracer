#pragma once
#include <glm.hpp>

#include "Ray.h"

//!Struct for intersections
struct Intersection	
{
	bool hit = false;	//!< Has Ray hit something?
	glm::vec3 intersectPoint;	//!< Where did it hit?
	float distanceToIntersect = INFINITY;	//!< How far is the intersection point from the origin
};

class Ray;
class Tracer;

//!Base Object Class
class Object
{
public:
	//! Pure virtual function,
	
	//! Which you cannot instantiate, every derived class mush override that function
	virtual Intersection RayInterect(Ray _ray) = 0;	

	//! Shade function - calucates the colour of the pixel
	virtual glm::vec3 Shade(Ray _ray, Tracer& _rayTracer, glm::vec3 _intersectPoint, int _traceBounce); 

	//virtual void SetNormal(glm::vec3 _intersecPoint) = 0; //!< Sets object surface normals
	virtual glm::vec3 GetNormal(glm::vec3 _intersectPoint) = 0;	//!< Gets object surface normals

	void SetPosition(glm::vec3 _pos) { position = _pos; }	//!< Sets Object position

	void SetColour(glm::vec3 _col) { colour = _col; }	//!< Sets Object Colour
	void SetReflection(float _refl) { reflection = _refl; }	//!< Sets Object Reflection

protected:
	glm::vec3 position;	//Object position
	glm::vec3 colour{ 0.0f };	//Object colour
	//glm::vec3 surfaceNormal;	//Object Surface Normal
	float reflection = 0;	//Reflection properties
};