#pragma once
#include <glm.hpp>
class Ray;
//!Camera Class
class Camera
{
public:
	Ray CreateRay(int x, int y);	//!<Shoots a Ray into the scene

	void SetScreenSize(int w, int h) { windowWidth = w; windowHeight = h; }	//!<Sets the Screen size

private:
	int windowWidth;
	int windowHeight;
};