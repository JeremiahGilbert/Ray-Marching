#include "Ray.h"

Ray::Ray(glm::vec3 const& position, glm::vec3 const& direction)
	: position_{position}, direction_{glm::normalize(direction)}, color_{glm::vec3{}} {}

void Ray::advance(float const distance) {
	position_ += direction_ * distance;
}

void Ray::blend_color(glm::vec3 const& color) {
	constexpr auto two_vector = glm::vec3{2};
	//color_ = glm::clamp(glm::sqrt(glm::pow(color_, two_vector) + glm::pow(color, two_vector)), glm::vec3{}, glm::vec3{1});

	color_ = glm::mix(color_, color, 0.5);
	//color_ = glm::max(color_, color);
}
