#include "Light.h"

Light::Light(glm::vec3 const& position, float const radius, Material const& material)
	: position_{position}, radius_{radius}, material_{material} {}

float Light::distance_to(glm::vec3 const& point) const {
	return glm::distance(point, position_) - radius_;
}
