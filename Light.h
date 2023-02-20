#pragma once
#include "Ray.h"
#include <vector>
#include <iostream>
#include "Polygons.h"
#include <random>
/*
This is the lightsource in the scene. It's rectangular and has a color of (1, 1, 1)
*/
class Light : public Polygons {
public:
	glm::dvec4 v0, v1, v2, v3;
	glm::dvec3 e1, e2;
	float area;
	
	//Could define a lightsource by calling the triangle constructor instead. Would be better
	Light();
	Light(glm::dvec4 _v0, glm::dvec4 _v1, glm::dvec4 _v2, glm::dvec4 _v3);

	virtual ColorRGB GetColor() const override;
	virtual glm::dvec3 GetNormal() const override;
	virtual int GetMaterial() const override;
	virtual float GetRho() const override;
	virtual bool Intersection(Ray& _ray) override;


private:
	glm::dvec3 normal;
	ColorRGB color = ColorRGB(1.0f);
	int material;
};