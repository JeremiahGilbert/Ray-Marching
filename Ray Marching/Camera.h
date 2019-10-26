#pragma once

#include <glm/glm.hpp>

#include "Ray.h"

class Camera {
public:
	Camera() = default;
	Camera(glm::vec3 const& position, glm::vec3 const& forward, glm::vec3 const& up, glm::vec2 const& image_resolution, float const fov);

	Ray create_ray_to_pixel(glm::vec2 const& pixel) const;

	inline glm::vec2 image_resolution() const {
		return image_resolution_;
	}

private:
	glm::mat4 view_matrix_;
	glm::mat4 inverse_projection_matrix_;

	// Render Surface
	glm::vec2 image_resolution_;
};
