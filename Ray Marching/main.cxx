#include <algorithm>
#include <execution>

#include <CImg.h>
#include <glm/glm.hpp>
#include <glm/vec2.hpp>

#include "Ray.h"
#include "Scene.h"

int main() {
	auto const [camera, scene] = Scene::load_scene_from_json("scene.json");

	auto const image_resolution = glm::uvec2{camera.image_resolution()};

	cimg_library::CImg<unsigned char> image{image_resolution.x, image_resolution.y, 1, 3};
	image.fill(0);

	auto horizontal_pixels = std::vector<unsigned int>{};
	horizontal_pixels.resize(image_resolution.x);
	std::iota(horizontal_pixels.begin(), horizontal_pixels.end(), 0);

	auto vertical_pixels = std::vector<unsigned int>{};
	vertical_pixels.resize(image_resolution.y);
	std::iota(vertical_pixels.begin(), vertical_pixels.end(), 0);

	std::for_each(std::execution::par_unseq, vertical_pixels.cbegin(), vertical_pixels.cend(), [&](auto const y) {
		std::for_each(std::execution::par_unseq, horizontal_pixels.cbegin(), horizontal_pixels.cend(), [&](auto const x) {
			auto ray = camera.create_ray_to_pixel(glm::vec2{x, y});
			auto const color = scene.raymarch(ray);

			image(x, y, 0) = static_cast<unsigned int>(color.r * 255);
			image(x, y, 1) = static_cast<unsigned int>(color.g * 255);
			image(x, y, 2) = static_cast<unsigned int>(color.b * 255);
		});
	});

	cimg_library::CImgDisplay display{image, "Ray Marching"};
	while (!display.is_closed()) {
		display.wait();
	}

	return 0;
}

