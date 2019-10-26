#include "Box.h"

#include <algorithm>

#include <glm/gtx/component_wise.hpp>

Box::Box(glm::vec3 const& position, glm::vec3 const& half_measures, Material const& material)
	: position_{position}, half_measures_{glm::abs(half_measures)}, material_{material} {}

float Box::distance_to(glm::vec3 const& point) const {
	auto q = glm::abs(point - position_) - half_measures_;
	return glm::length(glm::max(q, glm::vec3{})) + std::min(glm::compMax(q), 0.0f);
}
