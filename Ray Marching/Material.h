#pragma once

#include <glm/glm.hpp>

class Material {
public:
	Material() = default;
	Material(glm::vec3 const& color, float const reflectance, float const radiance);

	inline glm::vec3 color() const {
		return color_;
	}

	inline float reflectance() const {
		return reflectance_;
	}

	inline float radiance() const {
		return radiance_;
	}

private:
	glm::vec3 color_;
	float reflectance_;
	float radiance_;
};

