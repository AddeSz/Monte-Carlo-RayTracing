#include <glm/glm.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <chrono>
#include "Polygons.h"
#include "Ray.h"
#include "Camera.h"
#include "Scene.h"
#include "Light.h"

int main() {
	//Camera settings
	const int IMAGE_WIDTH = 800;
	const int IMAGE_HEIGHT = IMAGE_WIDTH;
	const int SAMPLES = 100;
	//Max depth incase we have infinite recursion between 2 mirros 
	const int MAXDEPTH = 100;
	const int SHADOWRAYS = 10;

	Camera c(IMAGE_WIDTH, IMAGE_HEIGHT, SAMPLES, MAXDEPTH, SHADOWRAYS);

	//Vertex list
	std::vector<glm::dvec4> vertexList;
	vertexList.reserve(14);
	vertexList.push_back(glm::dvec4(-3.0f, 0.0f, 5.0f, 1.0f));	//p0Roof
	vertexList.push_back(glm::dvec4(0.0f, 6.0f, 5.0f, 1.0f));	//p1Roof
	vertexList.push_back(glm::dvec4(10.0f, 6.0f, 5.0f, 1.0f));	//p2Roof
	vertexList.push_back(glm::dvec4(13.0f, 0.0f, 5.0f, 1.0f));	//p3Roof
	vertexList.push_back(glm::dvec4(10.0f, -6.0f, 5.0f, 1.0f));	//p4Roof
	vertexList.push_back(glm::dvec4(0.0f, -6.0f, 5.0f, 1.0f));	//p5Roof
	vertexList.push_back(glm::dvec4(5.0f, 0.0f, 5.0f, 1.0f));	//p6midRoof
	vertexList.push_back(glm::dvec4(-3.0f, 0.0f, -5.0f, 1.0f));	//p7Floor
	vertexList.push_back(glm::dvec4(0.0f, 6.0f, -5.0f, 1.0f));	//p8Floor
	vertexList.push_back(glm::dvec4(10.0f, 6.0f, -5.0f, 1.0f));	//p9Floor
	vertexList.push_back(glm::dvec4(13.0f, 0.0f, -5.0f, 1.0f));	//p1f0loor
	vertexList.push_back(glm::dvec4(10.0f, -6.0f, -5.0f, 1.0f)); //p11Floor
	vertexList.push_back(glm::dvec4(0.0f, -6.0f, -5.0f, 1.0f));	//p12Floor
	vertexList.push_back(glm::dvec4(5.0f, 0.0f, -5.0f, 1.0f));	//p13midFloor

	//Scene
	Scene scene = Scene(vertexList);
	//MATERIALS: 0 = DIFFUSE, 1 = MIRROR, 2 = LIGHT. 
	//Objects: Triangle, Lightsource(rectangle), Tetrahedron, Sphere
	scene.AddLightSource(Light(glm::dvec4(8.0f,-1.0f,5.0f,1.0f), glm::dvec4(8.0f, 1.0f, 5.0f, 1.0f), glm::dvec4(10.0f, -1.0f, 5.0f, 1.0f), glm::dvec4(10.0f, 1.0f, 5.0f, 1.0f)));
	scene.AddObject(std::make_shared<Sphere>(glm::dvec4(8.0f, 0.0f, -2.0f,1.0f), 1.0f, ColorRGB(1.0f, 0.0f, 0.0f), 1, 1.0f));
	scene.AddObject(std::make_shared<Tetrahedron>(glm::dvec4(7.0f, -5.0f, -4.0f, 1.0f), glm::dvec4(5.0f, -2.0f, -4.0f, 1.0f), glm::dvec4(7.0f, -1.0f, -4.0f, 1.0f), glm::dvec4(6.0f, -2.5f, 0.0f, 1.0f), ColorRGB(0.4f, 0.4f, 0.8f), 0, 0.8f));

	//Rendering
	auto start = std::chrono::high_resolution_clock::now();
	c.Render(scene);
	auto stop = std::chrono::high_resolution_clock::now();
	c.CreateImage();

	auto duration = std::chrono::duration<float, std::chrono::seconds::period> (stop - start);
	std::cout << "Time taken to render: "
		<< duration.count() << " seconds" << std::endl;
}