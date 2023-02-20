#pragma once
#include "Ray.h"
#include "Scene.h"
#include <glm/gtx/string_cast.hpp>

/*
This is the camera for the scene. It is located in (-1.0f, 0.0f, 0.0f, 1.0f)
*/
class Camera {
public:
	Camera(int _W, int _H, int _samples, int _maxDepth, int _shadowRays) : W{ _W }, H{ _H }, samples{ _samples }, maxDepth{ _maxDepth }, shadowRays{ _shadowRays } {}; 
	//Render function
	void Render(Scene& _scene);
	//Calculates reflection directions
	std::shared_ptr<Ray> MirrorReflection(std::shared_ptr<Ray> _inRay, std::shared_ptr<Polygons> _obj);
	std::shared_ptr<Ray> LambertianReflection(std::shared_ptr<Ray> _inRay, std::shared_ptr<Polygons> _obj);
	//Calculates the ray-paths
	std::shared_ptr<Ray> RayPaths(Scene& _scene, std::shared_ptr<Ray> _ray, int _maxDepth);
	//Creates final image
	void CreateImage();

	//Random uniform float
	float Random_float() {
		auto seed = std::mt19937{ std::random_device{}() }; //Random seed
		auto random = std::uniform_real_distribution<float>{ 0.f, 1.0f }; //Uniform distribution between -1 and 1 based on seed
		return random(seed);
	}

private:
	glm::dvec4 eyePos = glm::dvec4(-1.0f, 0.0f, 0.0f, 1.0f);
	int W, H, samples, maxDepth, shadowRays;
	using grid = std::vector<std::vector<Pixel>>;
	grid _pixels{ H, std::vector<Pixel>(W) };
};

