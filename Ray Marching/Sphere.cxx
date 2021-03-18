#include "Sphere.h"

Sphere::Sphere(glm::vec3 const& position, float const radius, std::string const& material_id)
	: position_{position}, radius_{radius}, material_id_{material_id} {}

float Sphere::distance_to(glm::vec3 const& point) const {
	return glm::distance(point, position_) - radius_;
}
