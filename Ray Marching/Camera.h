#pragma once

#include <cereal/cereal.hpp>
#include <glm/glm.hpp>

#include "GLM Serialization.h"
#include "Ray.h"

class Camera {
public:
	Camera() = default;
	Camera(glm::vec3 const& position, glm::vec3 const& forward, glm::vec3 const& up, glm::vec2 const& image_resolution, float const fov);

	Ray create_ray_to_pixel(glm::vec2 const& pixel) const;

	inline glm::vec2 image_resolution() const {
		return image_resolution_;
	}

	template<class Archive>
	void save(Archive& archive) const {
		archive(
			cereal::make_nvp("position", position_),
			cereal::make_nvp("forward", forward_),
			cereal::make_nvp("up", up_),
			cereal::make_nvp("image_resolution", image_resolution_),
			cereal::make_nvp("fov", fov_)
		);
	}

	template<class Archive>
	void load(Archive& archive) {
		auto position = glm::vec3{};
		archive(cereal::make_nvp("position", position));

		auto forward = glm::vec3{};
		archive(cereal::make_nvp("forward", forward));

		auto up = glm::vec3{};
		archive(cereal::make_nvp("up", up));

		auto image_resolution = glm::vec2{};
		archive(cereal::make_nvp("image_resolution", image_resolution));

		auto fov = 0.0f;
		archive(cereal::make_nvp("fov", fov));

		*this = Camera(position, forward, up, image_resolution, fov);
	}

private:
	glm::vec3 position_;
	glm::vec3 forward_;
	glm::vec3 up_;
	glm::vec2 image_resolution_;
	float fov_;

	glm::mat4 view_matrix_;
	glm::mat4 inverse_projection_matrix_;
};
