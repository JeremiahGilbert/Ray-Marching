#pragma once

#include <type_traits>

namespace opmath {

	template<typename Numeric>
	class range {
	public:
		range() = default;
		range(Numeric const lower_bound, Numeric const upper_bound) : lower_bound_{lower_bound}, upper_bound_{upper_bound} {};

		bool in_range(Numeric const value) const {
			return value >= lower_bound_ && value < upper_bound_;
		}

		float to_norm(Numeric const value) const {
			return (value - lower_bound_) / static_cast<float>(upper_bound_ - lower_bound_);
		}

		Numeric from_norm(float const norm) const {
			return norm * (upper_bound_ - lower_bound_) + lower_bound_;
		}

	private:
		Numeric lower_bound_;
		Numeric upper_bound_;
	};

	template<typename InputNumeric, typename OutputNumeric>
	OutputNumeric map_ranges(range<InputNumeric> const& input_range, range<OutputNumeric> const& output_range, InputNumeric const value) {
		auto const norm = input_range.to_norm(value);
		return output_range.from_norm(norm);
	}

	template<typename T>
	constexpr T pi() {
		return static_cast<T>(3.1415926535897932384626433832795L);
	}

	template<typename T>
	constexpr T e() {
		return static_cast<T>(2.7182818284590452353602874713527L);
	}

	template<typename T>
	constexpr T phi() {
		return static_cast<T>(1.6180339887498948482045868343656L);
	}

	template<typename T>
	constexpr T to_degrees(T radians) {
		return radians * static_cast<T>(180.0L) / pi<T>();
	}

	template<typename T>
	constexpr T to_radians(T degrees) {
		return degrees * pi<T>() / static_cast<T>(180.0L);
	}

}