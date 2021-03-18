#pragma once

#include <cereal/archives/json.hpp>

#include <glm/glm.hpp>

namespace cereal {

	template<class Archive>
	void serialize(Archive& archive, glm::vec2& vec) {
		archive(cereal::make_nvp("x", vec.x), cereal::make_nvp("y", vec.y));
	}

	template<class Archive>
	void serialize(Archive& archive, glm::vec3& vec) {
		archive(cereal::make_nvp("x", vec.x), cereal::make_nvp("y", vec.y), cereal::make_nvp("z", vec.z));
	}
}
