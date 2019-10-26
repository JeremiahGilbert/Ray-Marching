#include "Plane.h"

Plane::Plane(glm::vec3 const& normal, float const offset, Material const& material)
	: normal_{glm::normalize(normal)}, offset_{offset}, material_{material} {}

float Plane::distance_to(glm::vec3 const& point) const {
	return glm::dot(normal_, point) + offset_;
}
