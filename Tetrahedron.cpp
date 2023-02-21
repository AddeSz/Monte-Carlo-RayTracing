#include "Polygons.h"

Tetrahedron::Tetrahedron(glm::dvec4 _v0, glm::dvec4 _v1, glm::dvec4 _v2, glm::dvec4 _v3, ColorRGB _color) {
	color = _color;
	tList.push_back(Triangle(_v0, _v3, _v1, _color, material, rho));
	tList.push_back(Triangle(_v1, _v3, _v2, _color, material, rho));
	tList.push_back(Triangle(_v0, _v2, _v3, _color, material, rho));
	tList.push_back(Triangle(_v0, _v1, _v2, _color, material, rho));
}

Tetrahedron::Tetrahedron(glm::dvec4 _v0, glm::dvec4 _v1, glm::dvec4 _v2, glm::dvec4 _v3, ColorRGB _color, int _material) {
	color = _color;
	material = _material;

	tList.push_back(Triangle(_v0, _v3, _v1, _color, material, rho));
	tList.push_back(Triangle(_v1, _v3, _v2, _color, material, rho));
	tList.push_back(Triangle(_v0, _v2, _v3, _color, material, rho));
	tList.push_back(Triangle(_v0, _v1, _v2, _color, material, rho));
}

Tetrahedron::Tetrahedron(glm::dvec4 _v0, glm::dvec4 _v1, glm::dvec4 _v2, glm::dvec4 _v3, ColorRGB _color, int _material, float _rho) {
	color = _color;
	material = _material;
	rho = _rho;

	tList.push_back(Triangle(_v0, _v3, _v1, _color, material, rho));
	tList.push_back(Triangle(_v1, _v3, _v2, _color, material, rho));
	tList.push_back(Triangle(_v0, _v2, _v3, _color, material, rho));
	tList.push_back(Triangle(_v0, _v1, _v2, _color, material, rho));
}

ColorRGB Tetrahedron::GetColor() const {
	return this->color;
}

glm::dvec3 Tetrahedron::GetNormal() const {
	return this->normal;
}
//NO NEED
int Tetrahedron::GetMaterial() const {
	return this->material;
}

float Tetrahedron::GetRho() const {
	return this->rho;
}
//Make use of the triangle intersection test 
bool Tetrahedron::Intersection(Ray& _ray) {
	bool hitOne = false;
	
	for (int i = 0; i < 4; i++) {
		if (tList[i].Intersection(_ray)) {
			hitOne = true;
			//Outdated. Never use this normal
			this->normal = tList[i].GetNormal();
		}
	}

	if (hitOne) return true;
	else return false;
}
