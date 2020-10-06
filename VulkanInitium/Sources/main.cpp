#define GLFW_INCLUDE_VULKAN
#include "main.hpp"
#include "classes/HelloTriangleApplication.hpp"

int main() {
	//TestApplication app;
	HelloTriangleApplication app;

	try {
		app.run();
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}