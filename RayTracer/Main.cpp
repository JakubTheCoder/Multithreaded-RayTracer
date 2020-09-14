#include <iostream>
#include <cmath>
#include <future>
#include <mutex>

#include "CGG_Main.h"
#include "Camera.h"
#include "Ray.h"
#include "Tracer.h"
#include "Sphere.h"
#include "Plane.h"
#include <omp.h>

int main(int argc, char *argv[])
{
	auto timerStart = std::chrono::high_resolution_clock::now();	//Start Timer to check how long the ray tracer takes.

	int windowWidth = 640;
	int windowHeight = 480;

	if (!CGG::Init(windowWidth, windowHeight))
	{
		// We must check if something went wrong
		// (this is very unlikely)
		return -1;
	}

	CGG::SetBackground(0, 150, 255);	//Sets background to black

	//Create Objects
	Camera camera;
	Ray ray;
	Tracer rayTracer;
	glm::vec3 colour;

	camera.SetScreenSize(windowWidth, windowHeight);	//values for spawning rays

	
	//Scene
	Sphere sphere1;
	//sphere1.SetPosition(glm::vec3(0.0, 0.0f, -200.0f));	//ortho values
	//sphere1.SetRadius(50.0f);
	sphere1.SetPosition(glm::vec3(0.0f, 0.0f, -5.0f));	//proper camera values 
	sphere1.SetRadius(0.5f);
	sphere1.SetColour(glm::vec3(1.0f, 0.0f, 0.0f));
	
	Sphere sphere2;
	//sphere2.SetPosition(glm::vec3(-100.0f,0.0f,-200.0f));
	//sphere2.SetRadius(50.0f);
	sphere2.SetPosition(glm::vec3(0.7f, 0.7f, -5.0f));	
	sphere2.SetRadius(0.5f);
	sphere2.SetColour(glm::vec3(1.0f, 1.0f, 1.0f));

	Sphere sphere3;
	//sphere3.SetPosition(glm::vec3(0.0f, 100.0f, -200.0f));
	//sphere3.SetRadius(50.0f);
	sphere3.SetPosition(glm::vec3(-0.7f, 0.7f, -5.0f));
	sphere3.SetRadius(0.5f);
	sphere3.SetColour(glm::vec3(0.0f, 1.0f, 0.0f));
	sphere3.SetReflection(1.0f);

	Sphere sphere4;
	sphere4.SetPosition(glm::vec3(0.0f, 1.4f, -5.0f));
	sphere4.SetRadius(0.5f);
	sphere4.SetColour(glm::vec3(0.0f, 0.0f, 1.0f));
	sphere4.SetReflection(1.0f);


	Plane plane;
	plane.SetPosition(glm::vec3(0.0f, -1.2f, -0.1f));
	plane.SetColour(glm::vec3(0.4f, 0.3f,0.3f));
	
	//Push back objects to the ray tracer 
	rayTracer.AddObject((Object*)&sphere1);
	rayTracer.AddObject((Object*)&sphere2);
	rayTracer.AddObject((Object*)&sphere3);
	rayTracer.AddObject((Object*)&sphere4);
	rayTracer.AddObject((Object*)&plane);

	//Multithreading variables
	std::size_t size = windowWidth * windowHeight;
	std::size_t cores =  std::thread::hardware_concurrency();
	std::size_t threadCount = cores;
	volatile std::atomic<std::size_t>count = 0;
	std::vector<std::future<void>>future_vector;
	std::size_t index = 0;
	glm::vec3 *framebuffer = new glm::vec3[windowWidth*windowHeight];
	std::mutex mute;

	//Multithreading
	//WITHOUT ATOMICS
	//for (std::size_t i= 0; i < cores; ++i)future_vector.emplace_back(std::async([=, &ray,&rayTracer,&camera,&colour]()
	//{
	//	for (std::size_t index = i; index < size; index += cores)
	//	{
	//		std::size_t x = index % windowWidth;
	//		std::size_t y = index / windowWidth;

	//		ray = camera.CreateRay(x,y);	
	//		colour = rayTracer.TraceRay(ray, 1) * 255.0f;
	//		framebuffer[index] = colour;
	//	}
	//}));

	////WITH ATOMICS
	while (threadCount--)future_vector.emplace_back(std::async([=, &ray, &rayTracer, &camera, &colour, &count,&mute]()	//lambda expression
	{
		while (true)
		{
			//Count is a atmoic value, this value can be accessed by all variables but is the same no matter what thread
			//std::size_t index = count++;	//each thread gets its own index to work on
			//std::mutex lock the mutix, that line, increment counnt unlock mutex
			//mtx.lock();
			std::size_t index = count++;
			/*mute.lock();
			index = count;
			count++;
			mute.unlock();*/

			if (index >= size)	
			{
				break;
			}

			int x = index % windowWidth;
			int y = index / windowWidth;

			Ray tempRay = camera.CreateRay(x, y);	//cast ray at position
			glm::vec3 tempCol = rayTracer.TraceRay(tempRay,1) * 255.0f;	//Get the colour of the pixel by casting a ray into the scene 
			framebuffer[index] = tempCol;	//adds the colour to the framebuffer array to draw later on
		}
	}));

	//BOTH MULTITHREADING
	for (int i = 0; i < cores; ++i)	//wait for all threads to finish
	{
		future_vector.at(i).wait();
	}

	for (int i = 0; i < size; i++)	//Draw all the pixels from the frame buffer
	{
		int x = i % windowWidth;
		int y = i / windowWidth;
		CGG::DrawPixel(x, y, framebuffer[i].x, framebuffer[i].y, framebuffer[i].z);
	}

	////***************** non threaded*****************************
//#pragma omp parallel for
	//for (int y = 0; y < windowHeight; y++)	//SCREEN HEIGHT
	//{
	//	for (int x = 0; x < windowWidth; x++)	//SCREEN WIDTH
	//	{
	//		//std::async([=, &ray, &rayTracer, &camera, &colour]()
	//		//{
	//			ray = camera.CreateRay(x, y);
	//			//send ray into ray tracer
	//			colour = rayTracer.TraceRay(ray, 1) * 255.0f;
	//			//draw pixel
	////#pragma omp critical
	//			CGG::DrawPixel(x, y, colour.x, colour.y, colour.z);
	//		//});
	//	}
	//}
	auto timerEnd = std::chrono::high_resolution_clock::now();	//End timer to calulate difference 
	auto passedTime = std::chrono::duration<float, std::milli>(timerEnd - timerStart).count();	//calculate difference to find out how long project ran
	std::cout << "Time taken: " << passedTime / 1000 << " seconds " << std::endl;

	return CGG::ShowAndHold();
}

