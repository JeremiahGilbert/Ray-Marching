#pragma once

#include <glm/glm.hpp>

class Ray {
public:
	Ray() = default;
	Ray(glm::vec3 const& position, glm::vec3 const& direction);

	void advance(float const distance);

	void blend_color(glm::vec3 const& color);

	inline glm::vec3 position() const {
		return position_;
	};

	inline glm::vec3 direction() const {
		return direction_;
	}

	inline glm::vec3 color() const {
		return color_;
	}

	inline void color(glm::vec3 const& color) {
		color_ = color;
	}

private:
	glm::vec3 position_;
	glm::vec3 direction_;
	glm::vec3 color_;
};

