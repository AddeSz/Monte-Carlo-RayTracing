#include "Light.h"

Light::Light() {
	v0 = glm::dvec4(0.0f);
	v1 = glm::dvec4(0.0f);
	v2 = glm::dvec4(0.0f);
	v3 = glm::dvec4(0.0f);
	color = ColorRGB(1.0f);
	material = 2;

	e1 = glm::dvec3(0.0f);
	e2 = glm::dvec3(0.0f);
	normal = glm::dvec3(0.0f);
	area = 0.0f;
}
Light::Light(glm::dvec4 _v0, glm::dvec4 _v1, glm::dvec4 _v2, glm::dvec4 _v3 ) {
	v0 = _v0;
	v1 = _v1;
	v2 = _v2;
	v3 = _v3;
	color = ColorRGB(1.0f);
	material = 2;

	e1 = glm::dvec3(_v1 - _v0);
	e2 = glm::dvec3(_v2 - _v0);
	normal = glm::normalize(glm::cross(e1, e2));
	area = (float)glm::length(e1) * (float)glm::length(e2);
}

ColorRGB Light::GetColor() const {
	return this->color;
}

glm::dvec3 Light::GetNormal() const {
	return this->normal;
}

int Light::GetMaterial() const {
	return this->material;
}
//We do not have rho, just print am error message if that happens
float Light::GetRho() const {
	std::cout << "ERROR LIGHT DOES NOT HAVE RHO " << std::endl;
	return 1.0f;
}

//Use the triangle intersection test
bool Light::Intersection(Ray& _ray) {
	if (Triangle(v0, v1, v2, color, material).Intersection(_ray) || Triangle(v1, v3, v2, color, material).Intersection(_ray)) {
		return true;
	}
	else
		return false;
}