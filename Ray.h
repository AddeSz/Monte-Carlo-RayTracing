#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <iostream>
#include "Utility_Structs.h"
/*
This is the ray class. We have start point, end point and raydirection
*/
class Ray {
public:
	glm::dvec4 startPos, endPos;
	glm::dvec3 rayDir;
	ColorRGB rayColor; // not really used. 

	//This is like a pointer to the surface we hit. 
	double t;
	glm::dvec3 hitNormal = glm::dvec3(0.0f);
	float hitRho = 0;
	int hitMat = 0;
	ColorRGB hitColor = ColorRGB(0.0f);

	//Next and prev rays
	std::shared_ptr<Ray> prev = nullptr;
	std::shared_ptr<Ray> next = nullptr;

	Ray(const glm::dvec4& _startPos, const glm::dvec4& _endPos)
		: startPos{ _startPos }, endPos{ _endPos }, rayDir{ glm::normalize(_endPos - _startPos) }, rayColor{ ColorRGB(0.0f) }, t{ INFINITY } {};

	Ray(const glm::dvec4& _startPos, const glm::dvec3& _rayDir)
		: startPos{ _startPos }, rayDir{ glm::normalize(_rayDir) }, endPos{ glm::dvec4(NULL) }, rayColor{ ColorRGB(0.0f) }, t{INFINITY} {};

private:
};

