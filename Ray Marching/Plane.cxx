#include "Plane.h"

Plane::Plane(glm::vec3 const& normal, float const offset, std::string const& material_id)
	: normal_{glm::normalize(normal)}, offset_{offset}, material_id_{material_id} {}

float Plane::distance_to(glm::vec3 const& point) const {
	return glm::dot(normal_, point) + offset_;
}
