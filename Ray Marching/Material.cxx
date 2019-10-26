#include "Material.h"

Material::Material(glm::vec3 const& color, float const reflectance, float const radiance)
	: color_{glm::clamp(color, glm::vec3{0.0f}, glm::vec3{1.0f})}, reflectance_{reflectance}, radiance_{radiance} {}
