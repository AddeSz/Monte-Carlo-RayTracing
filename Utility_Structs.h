#pragma once
#include "glm/glm.hpp"
#include <iostream>
#include <memory>
#include <random>
/*
ColorRGB and pixel 
*/
struct ColorRGB {
	float r, g, b;
	bool type;

	ColorRGB()
		: r(0.0f), g(0.0f), b(0.0f), type{ true } {};

	ColorRGB(float _r, float _g, float _b)
		: r((float)_r), g((float)_g), b((float)_b), type{ true } {};

	ColorRGB(glm::dvec3 _color)
		: r((float)_color.r), g((float)_color.g), b((float)_color.b), type{ true } {};

	ColorRGB(float _n)
		: r((float)_n), g((float)_n), b((float)_n), type{ true } {};

	ColorRGB(const ColorRGB& cr)
		: r((float)cr.r), g((float)cr.g), b((float)cr.b), type{true} {};

	ColorRGB operator+(ColorRGB res) {
		this->r += res.r;
		this->g += res.g;
		this->b += res.b;
		return *this;
	}
	ColorRGB operator-(ColorRGB res) {
		this->r -= res.r;
		this->g -= res.g;
		this->b -= res.b;
		return *this;
	}
	ColorRGB operator-=(const ColorRGB& c) {
		this->r -= c.r;
		this->g -= c.g;
		this->b -= c.b;
		return *this;
	}
	ColorRGB operator+=(const ColorRGB& c) {
		this->r += c.r;
		this->g += c.g;
		this->b += c.b;
		return *this;
	}

	ColorRGB operator*=(const ColorRGB& c) {
		this->r *= c.r;
		this->g *= c.g;
		this->b *= c.b;
		return *this;
	}

	void PrintC() {
		std::cout << this->r << ", " << this->g << ", " << this->b << std::endl;
	}

	friend ColorRGB operator*(float t, const ColorRGB& c) {
		return ColorRGB(c.r * t, c.g * t, c.b * t);
	}
	friend ColorRGB operator*(const ColorRGB& c, float t) {
		return t * c;
	}
	friend ColorRGB operator*(const ColorRGB& c1, const ColorRGB& c2) {
		return ColorRGB(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b);
	}

	//friend ColorRGB operator/(float t, const ColorRGB& c) {
	//	return ColorRGB(c.r / t, c.g / t, c.b / t);
	//}
	friend ColorRGB operator/(const ColorRGB& c, float t) {
		return ColorRGB(c.r / t, c.g / t, c.b / t);
	}
	friend ColorRGB operator/(const ColorRGB& c1, const ColorRGB& c2) {
		return ColorRGB(c1.r / c2.r, c1.g / c2.g, c1.b / c2.b);
	}

	friend ColorRGB operator+(const glm::dvec3& c, ColorRGB vec) {
		return ColorRGB((float)c.x + vec.r, (float)c.y + vec.g, (float)c.z + vec.b);
	}
	friend ColorRGB operator+(ColorRGB vec, const glm::dvec3& c) {
		return c + vec;
	}

	//Does not work :/
	//friend ColorRGB operator==(const ColorRGB& c1, const ColorRGB& c2) {
	//	if ((std::fabs(c1.r - c2.r) < DBL_EPSILON) && (std::fabs(c1.g - c2.g) < DBL_EPSILON) && (std::fabs(c1.r - c2.r) < DBL_EPSILON)) {
	//		return true;
	//	}
	//	return false;
	//}
};

struct Pixel {
	Pixel() : color(ColorRGB(0.0f)), vert(glm::dvec4(0.0f, 0.0f, 0.0f, 1.0f)) {};

	Pixel(ColorRGB _c, glm::dvec4 _v) : color(_c), vert(_v) {};

	void getColor(ColorRGB _crl) {
		color.r = (_crl.r);
		color.g = (_crl.g);
		color.b = (_crl.b);
	}

	ColorRGB color;
	glm::dvec4 vert;
};
