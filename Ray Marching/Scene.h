#pragma once

#include <filesystem>
#include <map>
#include <variant>
#include <vector>

#include <cereal/cereal.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/variant.hpp>
#include <cereal/types/vector.hpp>

#include "Box.h"
#include "Camera.h"
#include "Light.h"
#include "Plane.h"
#include "Sphere.h"

using Shape = std::variant<Light, Plane, Sphere, Box>;

class Scene {
public:
	Scene() = default;
	Scene(float const epsilon, unsigned int const max_iterations, unsigned int const max_recursion_depth, std::map<std::string, Material> const& materials, std::vector<Shape> const& shapes);

	glm::vec3 raymarch(Ray ray, unsigned int const recursion_depth = 0) const;

	glm::vec3 reflection_scan(glm::vec3 const& surface_point, Ray const& incident_ray, unsigned int const recursion_depth = 0) const;

	glm::vec3 light_scan(glm::vec3 const& surface_point) const;

	glm::vec3 estimate_normal(glm::vec3 const& surface_point) const;

	float shadow_scan(Ray ray, float const distance) const;

	std::pair<Shape, float> get_nearest_shape(glm::vec3 const& point) const;

	template<class Archive>
	void serialize(Archive& archive) {
		archive(
			cereal::make_nvp("materials", materials_),
			cereal::make_nvp("shapes", shapes_),
			cereal::make_nvp("epsilon", epsilon_),
			cereal::make_nvp("max_iterations", max_iterations_),
			cereal::make_nvp("max_recursion_depth", max_recursion_depth_),
			cereal::make_nvp("sky_color", sky_color_),
			cereal::make_nvp("horizon_color", horizon_color_)
		);
	}

private:
	std::map<std::string, Material> materials_;
	std::vector<Shape> shapes_;

	glm::vec3 sky_color_ = glm::vec3{};
	glm::vec3 horizon_color_ = glm::vec3{};

	float epsilon_ = 0.001f;
	unsigned int max_iterations_ = 100;
	unsigned int max_recursion_depth_ = 1;
};

