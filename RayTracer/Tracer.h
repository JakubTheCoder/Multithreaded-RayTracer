#pragma once
#include <glm.hpp>
#include <vector>
#include <memory>
#include "Object.h"

class Ray;
class Object;
//!Ray Tracing Class
class Tracer
{
public:
	glm::vec3 TraceRay(Ray _ray, int _bounce);	//!< Trace Ray to get the colour of the closest intersect object
	bool ShadowRay(Ray _shadow);	//!< Trace Shadow Ray
	void AddObject(Object* object) //!< Adds Object to vector to calc tracing on
	{
		objects.push_back(object);
	}

private:
	std::vector<Object*> objects;
	int traceLimit = 6;	//!< Max number of Ray bounces
};
