#pragma once

#include <string>

#include <cereal/cereal.hpp>
#include <glm/glm.hpp>

#include "GLM Serialization.h"
#include "Material.h"

class Light {
public:
	Light() = default;
	Light(glm::vec3 const& position, float const radius, std::string const& material_id);

	float distance_to(glm::vec3 const& point) const;

	inline glm::vec3 position() const {
		return position_;
	}

	inline std::string material_id() const {
		return material_id_;
	}

	template<class Archive>
	void serialize(Archive& archive) {
		archive(cereal::make_nvp("position", position_), cereal::make_nvp("radius", radius_), cereal::make_nvp("material_id", material_id_));
	}

private:
	glm::vec3 position_;
	float radius_;

	std::string material_id_;
};

