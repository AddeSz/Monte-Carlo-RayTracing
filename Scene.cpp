#include "Scene.h"
Scene::Scene(const std::vector<glm::dvec4>& _vList) {
	//Roof
	Add(std::make_shared<Triangle>(_vList[0], _vList[1], _vList[6], ColorRGB(0.6f, 0.6f, 0.6f), 0, 0.8f));
	Add(std::make_shared<Triangle>(_vList[1], _vList[2], _vList[6], ColorRGB(0.6f, 0.6f, 0.6f), 0, 0.8f));
	Add(std::make_shared<Triangle>(_vList[2], _vList[3], _vList[6], ColorRGB(0.6f, 0.6f, 0.6f), 0, 0.8f));
	Add(std::make_shared<Triangle>(_vList[3], _vList[4], _vList[6], ColorRGB(0.6f, 0.6f, 0.6f), 0, 0.8f));
	Add(std::make_shared<Triangle>(_vList[4], _vList[5], _vList[6], ColorRGB(0.6f, 0.6f, 0.6f), 0, 0.8f));
	Add(std::make_shared<Triangle>(_vList[5], _vList[0], _vList[6], ColorRGB(0.6f, 0.6f, 0.6f), 0, 0.8f));
	
	//Floor
	Add(std::make_shared<Triangle>(_vList[8], _vList[7], _vList[13], ColorRGB(0.2f, 0.01f, 1.0f), 0, 0.5f));
	Add(std::make_shared<Triangle>(_vList[9], _vList[8], _vList[13], ColorRGB(0.2f, 0.01f, 1.0f), 0, 0.5f));
	Add(std::make_shared<Triangle>(_vList[10], _vList[9], _vList[13], ColorRGB(0.2f, 0.01f, 1.0f), 0, 0.5f));
	Add(std::make_shared<Triangle>(_vList[11], _vList[10], _vList[13], ColorRGB(0.2f, 0.01f, 1.0f), 0, 0.5f));
	Add(std::make_shared<Triangle>(_vList[12], _vList[11], _vList[13], ColorRGB(0.2f, 0.01f, 1.0f), 0, 0.5f));
	Add(std::make_shared<Triangle>(_vList[7], _vList[12], _vList[13], ColorRGB(0.2f, 0.01f, 1.0f), 0, 0.5f));
	

	//Behind camera walls 
	Add(std::make_shared<Triangle>(_vList[0], _vList[5], _vList[7], ColorRGB(1.0f, 0.8f, 0.01f), 0, 0.5f));
	Add(std::make_shared<Triangle>(_vList[5], _vList[12], _vList[7], ColorRGB(1.0f, 0.8f, 0.01f), 0, 0.5f));
	//correct
	Add(std::make_shared<Triangle>(_vList[0], _vList[7], _vList[8], ColorRGB(1.0f, 0.8f, 0.01f), 0, 0.5f));
	Add(std::make_shared<Triangle>(_vList[0], _vList[8], _vList[1], ColorRGB(1.0f, 0.8f, 0.01f), 0, 0.5f));

	//Left side wall
	Add(std::make_shared<Triangle>(_vList[12], _vList[5], _vList[4], ColorRGB(1.0f, 0.3f, 0.3f), 0, 0.5f));
	Add(std::make_shared<Triangle>(_vList[11], _vList[12], _vList[4], ColorRGB(1.0f, 0.3f, 0.3f), 0, 0.5f));
	//Left front wall
	Add(std::make_shared<Triangle>(_vList[11], _vList[4], _vList[3], ColorRGB(1.0f, 0.3f, 0.3f),0, 0.5f));
	Add(std::make_shared<Triangle>(_vList[10], _vList[11], _vList[3], ColorRGB(1.0f, 0.3f, 0.3f),0, 0.5f));

	//Right side wall
	Add(std::make_shared<Triangle>(_vList[1], _vList[8], _vList[9], ColorRGB(0.2f, 1.0f, 0.2f), 0, 0.5f));
	Add(std::make_shared<Triangle>(_vList[1], _vList[9], _vList[2], ColorRGB(0.2f, 1.0f, 0.2f), 0, 0.5f));
	//Right front wall
	Add(std::make_shared<Triangle>(_vList[2], _vList[9], _vList[10], ColorRGB(0.2f, 1.0f, 0.2f), 0, 0.5f));
	Add(std::make_shared<Triangle>(_vList[2], _vList[10], _vList[3], ColorRGB(0.2f, 1.0f, 0.2f), 0, 0.5f));
	
	/*
	//Roof
	Add(std::make_shared<Triangle>(_vList[0], _vList[1], _vList[6], ColorRGB(1.0f, 1.0f, 1.0f), 0, 0.8f));
	Add(std::make_shared<Triangle>(_vList[1], _vList[2], _vList[6], ColorRGB(1.0f, 1.0f, 1.0f), 0, 0.8f));
	Add(std::make_shared<Triangle>(_vList[2], _vList[3], _vList[6], ColorRGB(1.0f, 1.0f, 1.0f), 0, 0.8f));
	Add(std::make_shared<Triangle>(_vList[3], _vList[4], _vList[6], ColorRGB(1.0f, 1.0f, 1.0f), 0, 0.8f));
	Add(std::make_shared<Triangle>(_vList[4], _vList[5], _vList[6], ColorRGB(1.0f, 1.0f, 1.0f), 0, 0.8f));
	Add(std::make_shared<Triangle>(_vList[5], _vList[0], _vList[6], ColorRGB(1.0f, 1.0f, 1.0f), 0, 0.8f));

	//Floor
	Add(std::make_shared<Triangle>(_vList[8], _vList[7], _vList[13], ColorRGB(1.0f, 1.0f, 1.0f), 0, 0.5f));
	Add(std::make_shared<Triangle>(_vList[9], _vList[8], _vList[13], ColorRGB(1.0f, 1.0f, 1.0f), 0, 0.5f));
	Add(std::make_shared<Triangle>(_vList[10], _vList[9], _vList[13], ColorRGB(1.0f, 1.0f, 1.0f), 0, 0.5f));
	Add(std::make_shared<Triangle>(_vList[11], _vList[10], _vList[13], ColorRGB(1.0f, 1.0f, 1.0f), 0, 0.5f));
	Add(std::make_shared<Triangle>(_vList[12], _vList[11], _vList[13], ColorRGB(1.0f, 1.0f, 1.0f), 0, 0.5f));
	Add(std::make_shared<Triangle>(_vList[7], _vList[12], _vList[13], ColorRGB(1.0f, 1.0f, 1.0f), 0, 0.5f));


	//Behind camera walls 
	Add(std::make_shared<Triangle>(_vList[0], _vList[5], _vList[7], ColorRGB(1.0f, 1.0f, 1.0f), 0, 0.5f));
	Add(std::make_shared<Triangle>(_vList[5], _vList[12], _vList[7], ColorRGB(1.0f, 1.0f, 1.0f), 0, 0.5f));
	//correct
	Add(std::make_shared<Triangle>(_vList[0], _vList[7], _vList[8], ColorRGB(1.0f, 1.0f, 1.0f), 0, 0.5f));
	Add(std::make_shared<Triangle>(_vList[0], _vList[8], _vList[1], ColorRGB(1.0f, 1.0f, 1.0f), 0, 0.5f));

	//Left side wall
	Add(std::make_shared<Triangle>(_vList[12], _vList[5], _vList[4], ColorRGB(1.0f, 1.0f, 1.0f), 0, 0.5f));
	Add(std::make_shared<Triangle>(_vList[11], _vList[12], _vList[4], ColorRGB(1.0f, 1.0f, 1.0f), 0, 0.5f));
	//Left front wall
	Add(std::make_shared<Triangle>(_vList[11], _vList[4], _vList[3], ColorRGB(1.0f, 1.0f, 1.0f), 0, 0.5f));
	Add(std::make_shared<Triangle>(_vList[10], _vList[11], _vList[3], ColorRGB(1.0f, 1.0f, 1.0f), 0, 0.5f));

	//Right side wall
	Add(std::make_shared<Triangle>(_vList[1], _vList[8], _vList[9], ColorRGB(1.0f, 1.0f, 1.0f), 0, 0.5f));
	Add(std::make_shared<Triangle>(_vList[1], _vList[9], _vList[2], ColorRGB(1.0f, 1.0f, 1.0f), 0, 0.5f));
	//Right front wall
	Add(std::make_shared<Triangle>(_vList[2], _vList[9], _vList[10], ColorRGB(1.0f, 1.0f, 1.0f), 0, 0.5f));
	Add(std::make_shared<Triangle>(_vList[2], _vList[10], _vList[3], ColorRGB(1.0f, 1.0f, 1.0f), 0, 0.5f));
	*/
}

ColorRGB Scene::CalcDirectLight(glm::dvec4 _interSectionPoint, glm::dvec3 _normal, float _rho, int _shadowRays) {
	//Object recieves 0 direct light, if the normals point in the same way.
	float fastCheck = (float)glm::dot(_normal, this->lightSource.GetNormal());
	if (fastCheck > FLT_EPSILON) return ColorRGB(0.0f);

	ColorRGB color = ColorRGB(0.0f);
	float BRDF = _rho / (float)std::_Pi;
	
	auto seed = std::mt19937{ std::random_device{}() }; //Random seed
	auto random = std::uniform_real_distribution<float>{ 0.f, 1.f }; //Uniform distribution between 0 and 1 based on seed

	for (int i = 0; i < _shadowRays; i++) {
		// Two random values which are used for determining the position on the light source
		auto u = random(seed);
		auto v = random(seed);
		glm::dvec3 lightIntersectionPoint = glm::dvec3(this->lightSource.v0) + glm::dvec3(u) * this->lightSource.e1 + glm::dvec3(v) * this->lightSource.e2;
		glm::dvec3 distanceVector = lightIntersectionPoint - glm::dvec3(_interSectionPoint);
		float distToLight = (float)glm::length(distanceVector);

		//We shoot a shadowray towards that position and we check if we hit any objects in the scene. 
		Ray shadowRay = Ray(_interSectionPoint, glm::dvec4(lightIntersectionPoint, 1.0f));
		bool objHit = false;
		for (const auto& obj : this->objectList) {
			if (obj->Intersection(shadowRay)) {
				objHit = true;
				break; //We can break the loop if we hit something
			}
		}
		// If we dont hit a object = 0 color contribution
		if (!objHit) {
			//Geometric factor
			float cosX = (float)glm::max((float)glm::dot(glm::normalize(distanceVector), _normal), 0.0f);
			float cosY = (float)glm::max((float)glm::dot(-glm::normalize(distanceVector), this->lightSource.GetNormal()), 0.0f);

			color += BRDF * ((cosX * cosY) / (glm::pow(distToLight, 2)));
		}
	}

	return color * (this->lightSource.area / _shadowRays)*50;
}