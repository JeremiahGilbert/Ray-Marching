#include "Box.h"

#include <algorithm>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/component_wise.hpp>

Box::Box(glm::vec3 const& position, glm::vec3 const& rotation, glm::vec3 const& half_measures, std::string const& material_id)
	: position_{position},
	rotation_{rotation},
	transform_{glm::translate(glm::mat4{1.0f}, position_) * glm::mat4_cast(glm::quat{rotation_})},
	half_measures_{glm::abs(half_measures)},
	material_id_{material_id} {}

float Box::distance_to(glm::vec3 const& point) const {
	auto const inverse_transform_point = glm::vec3{glm::inverse(transform_) * glm::vec4{point, 1.0f}};

	auto const q = glm::vec3{glm::abs(inverse_transform_point)} - half_measures_;
	return glm::length(glm::max(q, glm::vec3{})) + std::min(glm::compMax(q), 0.0f);
}
