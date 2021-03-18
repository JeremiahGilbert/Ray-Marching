#pragma once

#include <string>

#include <cereal/cereal.hpp>
#include <glm/glm.hpp>

#include "GLM Serialization.h"
#include "Material.h"

class Plane {
public:
	Plane() = default;
	Plane(glm::vec3 const& normal, float const offset, std::string const& material_id);

	float distance_to(glm::vec3 const& point) const;

	inline std::string material_id() const {
		return material_id_;
	}

	template<class Archive>
	void serialize(Archive& archive) {
		archive(cereal::make_nvp("normal", normal_), cereal::make_nvp("offset", offset_), cereal::make_nvp("material_id", material_id_));
	}

private:
	glm::vec3 normal_;
	float offset_;

	std::string material_id_;
};

