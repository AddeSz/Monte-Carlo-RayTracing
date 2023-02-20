#pragma once
#include "Ray.h"
#include <vector>

/*
Here we define the polygons, each object has a color, normal, material type, reflectivity value and intersection test.

*/
class Polygons {
public:
	virtual ColorRGB GetColor() const = 0;
	virtual glm::dvec3 GetNormal() const = 0;
	virtual int GetMaterial() const = 0;
	virtual float GetRho() const = 0;
	virtual bool Intersection(Ray& _ray) = 0;
};

class Triangle : public Polygons {
public:
	Triangle();
	Triangle(glm::dvec4 _v0, glm::dvec4 _v1, glm::dvec4 _v2, ColorRGB _color);
	Triangle(glm::dvec4 _v0, glm::dvec4 _v1, glm::dvec4 _v2, ColorRGB _color, int _material);
	Triangle(glm::dvec4 _v0, glm::dvec4 _v1, glm::dvec4 _v2, ColorRGB _color, int _material, float _rho);

	virtual ColorRGB GetColor() const override;
	virtual glm::dvec3 GetNormal() const override;
	virtual int GetMaterial() const override;
	virtual float GetRho() const override;
	virtual bool Intersection(Ray& _ray) override;

private:
	glm::dvec4 v0, v1, v2;
	glm::dvec3 e1, e2;
	glm::dvec3 normal;
	ColorRGB color;
	int material = 0;
	float rho = 1.0f;
};


class Sphere : public Polygons {
public:
	Sphere(glm::dvec4 _center, float _radius, ColorRGB _color);
	Sphere(glm::dvec4 _center, float _radius, ColorRGB _color, int _material);
	Sphere(glm::dvec4 _center, float _radius, ColorRGB _color, int _material, float rho);

	virtual ColorRGB GetColor() const override;
	virtual glm::dvec3 GetNormal() const override;
	virtual int GetMaterial() const override;
	virtual float GetRho() const override;
	virtual bool Intersection(Ray& _ray) override;

private:
	ColorRGB color;
	glm::dvec4 center;
	glm::dvec3 normal;
	float radius, radius2;
	int material = 0;
	float rho = 1.0f;
};


class Tetrahedron : public Polygons {
public:
	//Should probably make a constructor for triangles intead. 
	Tetrahedron(glm::dvec4 _v0, glm::dvec4 _v1, glm::dvec4 _v2, glm::dvec4 _v3, ColorRGB _color);
	Tetrahedron(glm::dvec4 _v0, glm::dvec4 _v1, glm::dvec4 _v2, glm::dvec4 _v3, ColorRGB _color, int _material);
	Tetrahedron(glm::dvec4 _v0, glm::dvec4 _v1, glm::dvec4 _v2, glm::dvec4 _v3, ColorRGB _color, int _material, float _rho);

	virtual ColorRGB GetColor() const override;
	virtual glm::dvec3 GetNormal() const override;
	virtual int GetMaterial() const override;
	virtual float GetRho() const override;
	virtual bool Intersection(Ray& _ray) override;

private:
	glm::dvec3 normal = glm::dvec3(0.0f);
	std::vector<Triangle> tList;
	ColorRGB color;
	int material = 0;
	float rho = 1.0f;
};
