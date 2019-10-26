#pragma once

#include <glm/glm.hpp>

#include "Material.h"

class Plane {
public:
	Plane() = default;
	Plane(glm::vec3 const& normal, float const offset, Material const& material);

	float distance_to(glm::vec3 const& point) const;

	inline Material material() const {
		return material_;
	}

private:

	glm::vec3 normal_;
	float offset_;

	Material material_;
};

