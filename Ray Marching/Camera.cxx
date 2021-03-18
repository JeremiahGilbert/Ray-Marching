#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"

Camera::Camera(glm::vec3 const& position, glm::vec3 const& forward, glm::vec3 const& up, glm::vec2 const& image_resolution, float const fov)
	: position_{position},
	forward_{forward},
	up_{up},
	image_resolution_{image_resolution},
	fov_{fov},
	view_matrix_{glm::lookAt(position, position + forward, up * -1.0f)},
	inverse_projection_matrix_{glm::inverse(glm::perspective(glm::radians(fov), image_resolution.x / image_resolution.y, 0.01f, 100.0f))} {}

Ray Camera::create_ray_to_pixel(glm::vec2 const& pixel) const {
	auto const pixel_vector = pixel / image_resolution_ * 2.0f - 1.0f;

	auto const position = glm::vec3{view_matrix_ * glm::vec4{0.0f, 0.0f, 0.0f, 1.0f}};
	auto direction = glm::vec3{inverse_projection_matrix_ * glm::vec4{pixel_vector, 0.0f, 1.0f}};
	direction = glm::normalize(view_matrix_ * glm::vec4{direction, 0.0f});

	return Ray{position, direction};
}
