#include "Polygons.h"

Sphere::Sphere(glm::dvec4 _center, float _radius, ColorRGB _color) {
	center = _center;
	radius = _radius;
	color = _color;
	normal = glm::dvec3(0.0f);
	radius2 = radius * radius;
}
Sphere::Sphere(glm::dvec4 _center, float _radius, ColorRGB _color, int _material) {
	center = _center;
	radius = _radius;
	color = _color;
	normal = glm::dvec3(0.0f);
	material = _material;
	radius2 = radius * radius;
}

Sphere::Sphere(glm::dvec4 _center, float _radius, ColorRGB _color, int _material, float _rho) {
	center = _center;
	radius = _radius;
	color = _color;
	normal = glm::dvec3(0.0f);
	material = _material;
	rho = _rho;
	radius2 = radius * radius;
}

ColorRGB Sphere::GetColor() const {
	return this->color;
}

glm::dvec3 Sphere::GetNormal() const {
	return this->normal;
}

int Sphere::GetMaterial() const {
	return this->material;
}

float Sphere::GetRho() const {
	return this->rho;
}

//geometric solution. Could be further optimized 
bool Sphere::Intersection(Ray& _ray) {
	
	float t0, t1;
	glm::dvec3 centerVec = center - _ray.startPos;

	float tca = (float)glm::dot(centerVec, _ray.rayDir);
	if (tca < FLT_EPSILON) return false;
	float d2 = (float)glm::dot(centerVec, centerVec) - tca * tca;
	if (d2 > this->radius) return false;

	float thc = glm::sqrt(this->radius - d2);

	t0 = tca - thc;
	t1 = tca + thc;

	if (t0 > t1) std::swap(t0, t1);

	if (t0 < FLT_EPSILON) {
		t0 = t1;  //if t0 is negative use t1 instead
		if (t0 < FLT_EPSILON) return false;  //both t0 and t1 are negative 
	}

	if (t0 < _ray.t) {
		_ray.endPos = _ray.startPos + glm::dvec4((double)t0 * _ray.rayDir, 0.0f);
		this->normal = glm::dvec3(glm::normalize(_ray.endPos - center));
		_ray.t = t0;
		_ray.hitNormal = glm::dvec3(glm::normalize(_ray.endPos - center));
		_ray.hitRho = this->rho;
		_ray.hitColor = this->color;
		_ray.hitMat = this->material;
		return true;
	}

	return false;
}