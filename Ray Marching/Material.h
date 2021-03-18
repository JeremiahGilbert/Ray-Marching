#pragma once

#include <cereal/cereal.hpp>
#include <glm/glm.hpp>

#include "GLM Serialization.h"

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

	template<class Archive>
	void serialize(Archive& archive) {
		archive(cereal::make_nvp("color", color_), cereal::make_nvp("reflectance", reflectance_), cereal::make_nvp("radiance", radiance_));
	}

private:
	glm::vec3 color_;
	float reflectance_;
	float radiance_;
};

