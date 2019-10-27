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

	cimg_library::CImg<float> image{image_resolution.x, image_resolution.y, 1, 3};
	image.fill(0);
	image.permute_axes("cxyz");

	auto pixel_vectors = std::vector<Ray>{};
	for (auto y = 0u; y < image_resolution.y; ++y) {
		for (auto x = 0u; x < image_resolution.x; ++x) {
			pixel_vectors.emplace_back(camera.create_ray_to_pixel(glm::vec2{x, y}));
		}
	}
	
	std::transform(std::execution::par_unseq, pixel_vectors.cbegin(), pixel_vectors.cend(), reinterpret_cast<glm::vec3*>(image.begin()), [&](auto const& ray) {
		return scene.raymarch(ray);
	});

	image.permute_axes("yzcx");

	cimg_library::CImgDisplay display{image, "Ray Marching"};
	while (!display.is_closed()) {
		display.wait();
	}

	return 0;
}
