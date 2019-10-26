#include "Sphere.h"

Sphere::Sphere(glm::vec3 const& position, float const radius, Material const& material)
	: position_{position}, radius_{radius}, material_{material} {}

float Sphere::distance_to(glm::vec3 const& point) const {
	return glm::distance(point, position_) - radius_;
}
