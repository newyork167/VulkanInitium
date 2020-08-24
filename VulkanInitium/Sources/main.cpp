#define GLFW_INCLUDE_VULKAN
#include "main.hpp"

int main() {
	TestApplication app;

	try {
		app.run();
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}