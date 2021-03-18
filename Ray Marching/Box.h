#pragma once

#include <string>

#include <cereal/cereal.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "GLM Serialization.h"
#include "Material.h"

class Box {
public:
	Box() = default;
	Box(glm::vec3 const& position, glm::vec3 const& rotation, glm::vec3 const& half_measures, std::string const& material_id);

	float distance_to(glm::vec3 const& point) const;

	inline std::string material_id() const {
		return material_id_;
	}

	template<class Archive>
	void save(Archive& archive) const {
		archive(
			cereal::make_nvp("position", position_),
			cereal::make_nvp("rotation", rotation_),
			cereal::make_nvp("half_measures", half_measures_),
			cereal::make_nvp("material_id", material_id_)
		);
	}

	template<class Archive>
	void load(Archive& archive) {
		auto position = glm::vec3{};
		archive(cereal::make_nvp("position", position));

		auto rotation = glm::vec3{};
		archive(cereal::make_nvp("rotation", rotation));

		auto half_measures = glm::vec3{};
		archive(cereal::make_nvp("half_measures", half_measures));

		auto material_id = std::string{};
		archive(cereal::make_nvp("material_id", material_id));

		*this = Box(position, rotation, half_measures, material_id);
	}

private:
	glm::vec3 position_;
	glm::vec3 rotation_;
	glm::mat4 transform_;
	glm::vec3 half_measures_;

	std::string material_id_;
};

