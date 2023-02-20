#pragma once
#include "Ray.h"
#include <vector>
#include <iostream>
#include "Polygons.h"
#include "Light.h"

/*
This class defines all the objects in the scene. The room itself, lightsource etc 
*/
class Scene{
public:
	std::vector<Triangle> tList;
	std::vector<std::shared_ptr<Polygons>> sceneList;
	std::vector<std::shared_ptr<Polygons>> objectList;
	Light lightSource;

	//Creates the room
	Scene(const std::vector<glm::dvec4>& _vList);

	//adds a polygon to the scene
	Scene(std::shared_ptr<Polygons> __polygon) { Add(__polygon); };

	//Calculate the direct light that hits a lambertian surface
	ColorRGB CalcDirectLight(glm::dvec4 _interSectionPoint, glm::dvec3 _normal, float _rho, int _shadowRays);

	//Functions to add things to the scene
	void Add(std::shared_ptr<Polygons> _polygon) { sceneList.push_back(_polygon); };
	void AddObject(std::shared_ptr<Polygons> _polygon) { objectList.push_back(_polygon); };
	void AddLightSource(const Light& _polygon) {lightSource = Light(_polygon); };

};

