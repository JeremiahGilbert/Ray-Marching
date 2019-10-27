#include "Box.h"

#include <algorithm>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/component_wise.hpp>


Box::Box(glm::vec3 const& position, glm::vec3 const& rotation, glm::vec3 const& half_measures, Material const& material)
	: transform_{glm::translate(glm::mat4{1.0f}, position) * glm::mat4_cast(glm::quat{rotation})},
	half_measures_{glm::abs(half_measures)},
	material_{material} {}

float Box::distance_to(glm::vec3 const& point) const {
	auto const inverse_transform_point = glm::vec3{glm::inverse(transform_) * glm::vec4{point, 1.0f}};

	auto const q = glm::vec3{glm::abs(inverse_transform_point)} - half_measures_;
	return glm::length(glm::max(q, glm::vec3{})) + std::min(glm::compMax(q), 0.0f);
}
