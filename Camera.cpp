#include <iostream>
#include <fstream>
#include "Camera.h"
#include <glm/glm.hpp>
#include "Polygons.h"
#include "Light.h"

//Mirror reflection direction calculation
std::shared_ptr<Ray> Camera::MirrorReflection(std::shared_ptr<Ray> _inRay, std::shared_ptr<Polygons> _obj) {
	glm::dvec3 newRayDir = _inRay->rayDir + glm::dvec3(-2.0f) * (glm::dot(_inRay->rayDir, _obj->GetNormal()) * _obj->GetNormal());
	auto r = std::make_shared<Ray>(_inRay->endPos, glm::normalize(newRayDir));
	_inRay->next = r;
	r->prev = _inRay;
	return r;
}
//Lambertian reflection direction calculation
std::shared_ptr<Ray> Camera::LambertianReflection(std::shared_ptr<Ray> _inRay, std::shared_ptr<Polygons> _obj) {
	//Form the basis 
	glm::dvec3 Z = { _obj->GetNormal() };
	glm::dvec3 X = glm::normalize(-_inRay->rayDir + glm::dot(_inRay->rayDir, Z) * Z);
	glm::dvec3 Y = glm::cross(X, Z);

	//Tried making it according to lecture notes but it didn't work. So it's a mix between what was written in the "Raytracing in a weekend" book and lecture notes. 
	float phi = 2 * (float)std::_Pi * Random_float();
	float theta = glm::acos(2 * Random_float() - 1.0f);
	float x = glm::cos(phi) * glm::sin(theta);
	float y = glm::sin(phi) * glm::sin(theta);
	float z = glm::cos(theta);

	std::shared_ptr<Ray> r;
	glm::dvec3 newRayDir = glm::normalize(glm::dmat3(X, Y, Z) * glm::dvec3(x, y, z));

	//Pick correct side of the hemisphere
	if (glm::dot(newRayDir, _obj->GetNormal()) > 0.0f) {
		r = std::make_shared<Ray>(_inRay->endPos, newRayDir);
	}
	else {
		r = std::make_shared<Ray>(_inRay->endPos, -newRayDir);
	}
	_inRay->next = r;
	r->prev = _inRay;
	return r;
}

//Compute all ray-paths
std::shared_ptr<Ray> Camera::RayPaths(Scene& _scene, std::shared_ptr<Ray> _ray, int _maxDepth) {
	//Check this incase we have infinite recursion betweeen 2 mirros for example
	if (_maxDepth == 0) {
		return _ray;
	}
	else _maxDepth--;

	float randomNumber = Random_float();

	auto rOut = _ray;
	bool objectHitCheck = false;
	std::shared_ptr<Polygons> objectHit = nullptr;
	if (_scene.objectList.size() > 0) {
		auto objectHit = _scene.objectList.front();
	}

	//Check for objects inside the scene
	for (const auto& obj : _scene.objectList) {
		if (obj->Intersection(*_ray)) {
			objectHitCheck = true;
			objectHit = obj;
		}
	}
	//If we have objects inside the scen:
	if (objectHitCheck) {
		if (objectHit->GetMaterial() == 1) {//Mirror
			rOut = RayPaths(_scene, MirrorReflection(_ray, objectHit), _maxDepth);
		}
		else if (objectHit->GetMaterial() == 0) { //Lambertian 
			if ( objectHit->GetRho() > randomNumber) {
				rOut = RayPaths(_scene, LambertianReflection(_ray, objectHit), _maxDepth);
			}
			else {
				return rOut;
			}
		}
	}

	//if we hit a object inside the scene a lightsource/wall wont be closer
	//Check for light source intersections
	Light lightSource1 = _scene.lightSource;
	if (lightSource1.Intersection(*_ray)) {
		return rOut;
	}

	//Check for scene intersections
	for (const auto& obj : _scene.sceneList) {
		if (obj->Intersection(*_ray)) {
			if (obj->GetMaterial() == 1) { //Mirror
				rOut = RayPaths(_scene, MirrorReflection(_ray, obj), _maxDepth);
			}
			else if (obj->GetMaterial() == 0) { //Lambartian reflector
				if (obj->GetRho() > randomNumber) {
					rOut = RayPaths(_scene, LambertianReflection(_ray, obj), _maxDepth);
				}
				else {
					return rOut;
				}
				
			}
		}
	}
	return rOut;
}


//Calculates the color for each pixel
void Camera::Render(Scene& _scene) {
	for (int j = 0; j < H; ++j) {
		std::cerr << "\rScanlines remaining: " << H - 1 - j << ' ' << std::flush;
		for (int i = 0; i < W; ++i) {

			ColorRGB pixel_color(0.0f);
			
			//Kinda messy but it works and looks ok for higher sample values.
			for (int k = 0; k < samples; k++) {
				float y = ((float)(i + Random_float())/(W/2) - 1.f);
				float z = ((float)(j + Random_float())/(H/2) - 1.f);

				auto rStart = std::make_shared<Ray>(eyePos, glm::dvec3(glm::vec3(0, y, -z) - glm::vec3(eyePos)));
				auto rEnd = RayPaths(_scene, rStart, maxDepth);
				
				//MATERIALS: 0 = DIFFUSE, 1 = MIRROR, 2 = LIGHT.
				//Tried making this according to lecture notes but it looks very bad
				ColorRGB ray_color(0.0f);
				if (rEnd->hitMat == 2) {
					//ray_color += ColorRGB(1.0f);
					ray_color = ColorRGB(1.0f);
				}
				else {
					//ray_color += _scene.CalcDirectLight(rEnd->endPos, rEnd->hitNormal, rEnd->hitRho, shadowRays);
					ray_color = rEnd->hitColor * _scene.CalcDirectLight(rEnd->endPos, rEnd->hitNormal, rEnd->hitRho, shadowRays);
				}

				while (rEnd->prev != nullptr) {
					rEnd = rEnd->prev;
					if (rEnd->hitMat != 1) {
						//ray_color = rEnd->hitColor * ray_color + _scene.CalcDirectLight(rEnd->endPos, rEnd->hitNormal, rEnd->hitRho, shadowRays);
						ray_color = rEnd->hitColor * ray_color + rEnd->hitColor * _scene.CalcDirectLight(rEnd->endPos, rEnd->hitNormal, rEnd->hitRho, shadowRays);
					}
					rEnd->next.reset();
				}
				
				pixel_color += ray_color;
				rStart.reset();
			}
			_pixels[j][i].getColor(pixel_color / (float)samples);
		}
	}
	std::cout << std::endl;
}

void Camera::CreateImage() {
	std::ofstream ofs("./image.ppm", std::ios::out | std::ios::binary);
	ofs << "P6\n" << W << " " << H << "\n255\n";
	float maxIntensity = 0.0f;
	float minIntensity = 0.0f;
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			const ColorRGB& color = _pixels[i][j].color;
			float maxOfPixel = glm::max(glm::max(color.r, color.g), color.b);
			float minOfPixel = glm::min(glm::min(color.r, color.g), color.b);

			if (maxOfPixel > maxIntensity) {
				maxIntensity = maxOfPixel;
			}
			if (minIntensity > minOfPixel) {
				minIntensity = minOfPixel;
			}
				
		}
	}
	std::cout << "Max intensity:" << maxIntensity << std::endl;
	std::cout << "Min intensity:" << minIntensity << std::endl;

	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			/*
			double r = pixels[i][j].color.x();
			double g = pixels[i][j].color.y();
			double b = pixels[i][j].color.z();

			ofs << unsigned char(256 * glm::clamp((float)glm::sqrt(r), 0.0f, 0.99f))
				<< unsigned char(256 * glm::clamp((float)glm::sqrt(g), 0.0f, 0.99f))
				<< unsigned char(256 * glm::clamp((float)glm::sqrt(b), 0.0f, 0.99f));
			//std::cout << "(" << r << "," << g << "," << b << ")" << std::endl;
			*/
			//unsigned char r = static_cast<unsigned char>(glm::clamp(_pixels[i][j].color.r, 0.0f, 1.f) * 255 / 1);
			//unsigned char g = static_cast<unsigned char>(glm::clamp(_pixels[i][j].color.g, 0.0f, 1.f) * 255 / 1);
			//unsigned char b = static_cast<unsigned char>(glm::clamp(_pixels[i][j].color.b, 0.0f, 1.f) * 255 / 1);

			unsigned char r = static_cast<unsigned char>(_pixels[i][j].color.r * 255.f/ maxIntensity);
			unsigned char g = static_cast<unsigned char>(_pixels[i][j].color.g * 255.f/ maxIntensity);
			unsigned char b = static_cast<unsigned char>(_pixels[i][j].color.b * 255.f/ maxIntensity);

			ofs << r << g << b;
		}
	}
	ofs.close();
}