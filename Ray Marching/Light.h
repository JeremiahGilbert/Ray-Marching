#pragma once

#include <glm/glm.hpp>

#include "Material.h"

class Light {
public:
	Light() = default;
	Light(glm::vec3 const& position, float const radius, Material const& material);

	float distance_to(glm::vec3 const& point) const;

	inline glm::vec3 position() const {
		return position_;
	}

	inline Material material() const {
		return material_;
	}

private:
	glm::vec3 position_;
	float radius_;

	Material material_;
};

