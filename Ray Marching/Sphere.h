#pragma once
#include <glm/glm.hpp>

#include "Material.h"

class Sphere {
public:
	Sphere() = default;
	Sphere(glm::vec3 const& position, float const radius, Material const& material);

	float distance_to(glm::vec3 const& point) const;

	inline Material material() const {
		return material_;
	}

private:
	glm::vec3 position_;
	float radius_;

	Material material_;
};
