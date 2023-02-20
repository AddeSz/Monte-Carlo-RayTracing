#include "Polygons.h"

Triangle::Triangle() {
	v0 = glm::dvec4(0.0f);
	v1 = glm::dvec4(0.0f);
	v2 = glm::dvec4(0.0f);
	color = ColorRGB(0.0f);
	material = 0;

	e1 = glm::dvec3(v1 - v0);
	e2 = glm::dvec3(v2 - v0);
	normal = glm::dvec3(0.0f);
}

Triangle::Triangle(glm::dvec4 _v0, glm::dvec4 _v1, glm::dvec4 _v2, ColorRGB _color) {
	v0 = _v0;
	v1 = _v1;
	v2 = _v2;
	color = _color;
	material = 0;

	e1 = glm::dvec3(_v1 - _v0);
	e2 = glm::dvec3(_v2 - _v0);
	normal = glm::normalize(glm::cross(e1, e2));
}

Triangle::Triangle(glm::dvec4 _v0, glm::dvec4 _v1, glm::dvec4 _v2, ColorRGB _color, int _materialID) {
	v0 = _v0;
	v1 = _v1;
	v2 = _v2;
	color = _color;
	material = _materialID;

	e1 = glm::dvec3(_v1 - _v0);
	e2 = glm::dvec3(_v2 - _v0);
	normal = glm::normalize(glm::cross(e1, e2));
}

Triangle::Triangle(glm::dvec4 _v0, glm::dvec4 _v1, glm::dvec4 _v2, ColorRGB _color, int _materialID, float _rho) {
	v0 = _v0;
	v1 = _v1;
	v2 = _v2;
	color = _color;
	material = _materialID;
	rho = _rho;

	e1 = glm::dvec3(_v1 - _v0);
	e2 = glm::dvec3(_v2 - _v0);
	normal = glm::normalize(glm::cross(e1, e2));
}

ColorRGB Triangle::GetColor() const {
	return this->color;
}

glm::dvec3 Triangle::GetNormal() const {
	return this->normal;
}

int Triangle::GetMaterial() const {
	return this->material;
}

float Triangle::GetRho() const {
	return this->rho;
}

//möller-trumbore algorithm
bool Triangle::Intersection(Ray& _ray) {
	glm::dvec3 P = glm::cross(_ray.rayDir, e2);
	double det = glm::dot(e1, P);
	//If the determinant is negative the triangle is 'back facing'
	if (det < FLT_EPSILON) return false; 
	//Ray and triangle are parallel if det is close to 0
	if (glm::abs(det) < FLT_EPSILON) return false;
	

	double invDet = 1.0 / det; 

	glm::dvec3 T = glm::dvec3(_ray.startPos - v0);
	double u = glm::dot(T, P) * invDet;
	if (u < 0 || u > 1) return false;
	
	glm::dvec3 Q = glm::cross(T, e1);
	double v = glm::dot(_ray.rayDir, Q) * invDet;
	if (v < 0.0 || u + v > 1.0) return false;
	double t = glm::dot(e2, Q) * invDet;

	//If t is smaller than _ray.r, the object is closer
	if (t < _ray.t && t > FLT_EPSILON) {
		_ray.endPos = _ray.startPos + glm::dvec4(t * _ray.rayDir, 1.0f);
		_ray.hitNormal = this->normal;
		_ray.hitRho = this->rho;
		_ray.hitColor = this->color;
		_ray.hitMat = this->material;
		_ray.t = t;
		return true;
	}
	else {
		return false;
	}
}