
#include "Object.h"
#include "Tracer.h"

glm::vec3 Object::Shade(Ray _ray, Tracer &_rayTracer, glm::vec3 _intersectPoint, int _traceBounce)
{
	glm::vec3 lightPos = { 0.0f,1.0f,-3.0f };
	glm::vec3 lightDir = { 0.0f, 1.0f, 1.0f };//-lightPos;	//Sets Light Direction
	glm::vec3 lightCol = { 1.0f,1.0f,1.0f };	//Sets Light colour (white)
	lightDir = glm::normalize(lightDir);	//Normalize light direction
	//SetNormal(_intersectPoint);	//Set object surface normal
	glm::vec3 surfaceNormal = GetNormal(_intersectPoint);	//Get object surface normal
	glm::vec3 diffuseColour{ 0.0f };	//Set object diffuse colour 

	//shadows
	//send ray from intersection point to light source
	//light source doesn't have a pos :/ -light direction?
	//Shadow trace function to trace ray and return if there is a hit
	//the object order does not matter since the object is in shadow
	//set colour to

	Ray shadowRay;	//Creates Shadow Ray from intersection point to light source
	shadowRay.origin = _intersectPoint + lightDir * 0.001f;
	shadowRay.direction = lightDir;


	bool inShadow;
	inShadow = _rayTracer.ShadowRay(shadowRay);	

	if (inShadow == false)	//If Object is not in shadow return the colour of the object
	{
		float dot = glm::dot(lightDir, surfaceNormal);	
		
		if (dot > 0)
		{
			diffuseColour = dot * (lightCol * colour);
			glm::vec3 specColour = glm::pow(dot, 20)*(1.0f - diffuseColour);
			diffuseColour += specColour;

		}
	}

	//Reflection
	if (reflection > 0)
	{
		glm::vec3 reflCol{ 0.0f };	//reflection colour
		//reflect direction
		glm::vec3 reflect = glm::normalize(_ray.direction - 2.0f * glm::dot(_ray.direction, surfaceNormal)*surfaceNormal);
		//Create reflection Ray 
		Ray reflectRay;
		reflectRay.origin = _intersectPoint + reflect * 0.0001f;
		reflectRay.direction = reflect;
		reflCol = _rayTracer.TraceRay(reflectRay, _traceBounce + 1);	//Trace the new ray and increase the amount of ray trace bounces
		diffuseColour += reflection * reflCol;	//add the reflection colour to the diffuse colour
	}
	return glm::clamp(diffuseColour, glm::vec3(0),glm::vec3(1));	//makes sure values are between 0 and 1 
}