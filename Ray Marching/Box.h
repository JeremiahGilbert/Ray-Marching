#pragma once

#include <glm/glm.hpp>

#include "Material.h"

class Box {
public:
	Box() = default;
	Box(glm::vec3 const& position, glm::vec3 const& half_measures, Material const& material);

	float distance_to(glm::vec3 const& point) const;

	inline Material material() const {
		return material_;
	}

private:
	glm::vec3 position_;
	glm::vec3 half_measures_;

	Material material_;
};

