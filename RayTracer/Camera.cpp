#include "Camera.h"
#include "Ray.h"
#include <ext.hpp>
Ray Camera::CreateRay(int x, int y)
{
	//orthographic view
	//rays origin will be vec 3 x - half width , y - half height z = 0;
	//Ray ray;	//create ray
	//ray.origin = glm::vec3(x - (windowWidth / 2), y - (windowHeight / 2), 0);	//spawn it at the center of the screen
	//ray.direction = glm::vec3(0.0f, 0.0f, -1.0f);	//Send ray backwords


	//Projection Matrix
	glm::vec4 nearPlane;
	nearPlane.x = ((float)x / ((float)windowWidth / 2.0f)) - 1.0f;
	nearPlane.y = -(((float)y / ((float)windowHeight / 2.0f)) - 1.0f);	//top left of cube = -1,1 
	nearPlane.z = -1;
	nearPlane.w = 1;


	glm::vec4 farPlane;
	farPlane.x = ((float)x / ((float)windowWidth / 2.0f)) -1.0f;
	farPlane.y = -(((float)y / ((float)windowHeight / 2.0f)) - 1.0f);
	farPlane.z = 1;
	farPlane.w = 1;

	//create projection matrix
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
	
	nearPlane = (glm::inverse(projection) * nearPlane);

	farPlane = (glm::inverse(projection) * farPlane);

	nearPlane /= nearPlane.w;
	farPlane /= farPlane.w;

	//view matrix
	glm::mat4 view(1);	//does nothing so far, change if you want to move / rotate camera

	nearPlane = glm::inverse(view) * nearPlane;

	farPlane = glm::inverse(view) * farPlane;

	Ray ray;
	ray.origin = glm::vec3(nearPlane);
	ray.direction = glm::normalize(-ray.origin + glm::vec3(farPlane));
	return ray;
}