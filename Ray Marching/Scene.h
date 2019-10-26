#pragma once

#include <filesystem>
#include <map>
#include <variant>
#include <vector>

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
	
	static std::pair<Camera, Scene> load_scene_from_json(std::filesystem::path const& path);

private:
	std::map<std::string, Material> materials_;
	std::vector<Shape> shapes_;

	float epsilon_;
	unsigned int max_iterations_;
	unsigned int max_recursion_depth_;
};

