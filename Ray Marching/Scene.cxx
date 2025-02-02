#include "Scene.h"

#include <fstream>

#include <glm/glm.hpp>

Scene::Scene(float const epsilon, unsigned int const max_iterations, unsigned int const max_recursion_depth, std::map<std::string, Material> const& materials, std::vector<Shape> const& shapes)
	: epsilon_{epsilon}, max_iterations_{max_iterations}, max_recursion_depth_{max_recursion_depth}, materials_{materials}, shapes_{shapes} {}

glm::vec3 Scene::raymarch(Ray ray, unsigned int const recursion_depth) const {
	for (auto iterations = 0u; iterations < max_iterations_; ++iterations) {
		auto const [nearest_shape, distance_to_nearest] = get_nearest_shape(ray.position());

		if (distance_to_nearest < epsilon_) {
			auto const surface_point = ray.position() + ray.direction() * distance_to_nearest;
			return std::visit([&](auto const& shape) {
				using T = std::decay_t<decltype(shape)>;

				auto const material = materials_.at(shape.material_id());
				if constexpr (std::is_same_v<T, Light>) {
					return material.color();
				}

				auto reflection_color = glm::vec3{1.0f};
				auto const reflectance = material.reflectance();
				if (reflectance > 0.0f) {
					reflection_color = reflection_scan(surface_point, ray, recursion_depth);
				}

				return glm::mix(material.color() * light_scan(surface_point), reflection_color, reflectance);
			}, nearest_shape);
		}
		ray.advance(distance_to_nearest);
	}

	return glm::mix(horizon_color_, sky_color_, glm::dot(ray.direction(), glm::vec3{0, 1, 0}));
}

glm::vec3 Scene::reflection_scan(glm::vec3 const& surface_point, Ray const& incident_ray, unsigned int const recursion_depth) const {
	auto const normal = estimate_normal(surface_point);
	auto reflected_ray = Ray{surface_point, glm::reflect(incident_ray.direction(), normal)};
	reflected_ray.advance(2 * epsilon_);

	if (recursion_depth < max_recursion_depth_) {
		return raymarch(reflected_ray, recursion_depth + 1);
	}
	return glm::vec3{1.0f};
}

glm::vec3 Scene::light_scan(glm::vec3 const& surface_point) const {
	auto output_color = glm::vec3{};
	auto const normal = estimate_normal(surface_point);

	for (auto const& shape : shapes_) {
		if (std::holds_alternative<Light>(shape)) {
			auto const light = std::get<Light>(shape);
			auto const light_material = materials_.at(light.material_id());
			auto const to_light = glm::normalize(light.position() - surface_point);

			auto const distance_to_light = glm::distance(light.position(), surface_point);
			auto const brightness = light_material.radiance() / std::powf(distance_to_light, 2);
			auto const diffuse_angle = glm::clamp(glm::dot(normal, to_light), 0.0f, 1.0f);

			// Shadow Calculation
			auto const surface_offset = surface_point + normal * epsilon_ * 2.0f;
			auto const offset_distance_to_light = glm::distance(light.position(), surface_offset);

			auto const ray = Ray{surface_offset, to_light};
			auto const shadow = shadow_scan(ray, offset_distance_to_light);

			output_color += light_material.color() * brightness * diffuse_angle * shadow;
			output_color = glm::clamp(output_color, glm::vec3{0.01f}, glm::vec3{1.0f});
		}
	}
	return output_color;
}

glm::vec3 Scene::estimate_normal(glm::vec3 const& surface_point) const {
	auto const x = get_nearest_shape(surface_point + glm::vec3{epsilon_, 0, 0}).second - get_nearest_shape(surface_point - glm::vec3{epsilon_, 0, 0}).second;
	auto const y = get_nearest_shape(surface_point + glm::vec3{0, epsilon_, 0}).second - get_nearest_shape(surface_point - glm::vec3{0, epsilon_, 0}).second;
	auto const z = get_nearest_shape(surface_point + glm::vec3{0, 0, epsilon_}).second - get_nearest_shape(surface_point - glm::vec3{0, 0, epsilon_}).second;
	return glm::normalize(glm::vec3{x, y, z});
}

float Scene::shadow_scan(Ray ray, float const distance_to_light) const {
	auto constexpr shadow_intensity = 0.2f;
	auto ray_distance = 0.0f;
	auto brightness = 1.0f;

	while (ray_distance < distance_to_light) {
		auto const [nearest_shape, distance_to_nearest] = get_nearest_shape(ray.position());

		if (distance_to_nearest < epsilon_) {
			if (std::holds_alternative<Light>(nearest_shape)) {
				return 1.0f;
			}
			return shadow_intensity;
		}

		brightness = std::min(brightness, 20 * distance_to_nearest);
		ray.advance(distance_to_nearest);
		ray_distance += distance_to_nearest;
	}

	return shadow_intensity + (1.0f - shadow_intensity) * brightness;
}


std::pair<Shape, float> Scene::get_nearest_shape(glm::vec3 const& point) const {
	auto nearest_shape = Shape{};
	auto distance_to_nearest = std::numeric_limits<float>::infinity();

	for (auto const& shape : shapes_) {
		std::visit([&](auto const& shape) {
			auto const distance_to_shape = shape.distance_to(point);
			if (distance_to_shape < distance_to_nearest) {
				distance_to_nearest = distance_to_shape;
				nearest_shape = shape;
			}
		}, shape);
	}

	return std::pair<Shape, float>{nearest_shape, distance_to_nearest};
}
