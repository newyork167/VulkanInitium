#pragma once

const double ASPECT_RATIO = 16.0 / 9.0;
const uint32_t WIDTH = 1920;
const uint32_t HEIGHT = WIDTH / ASPECT_RATIO;

class TestApplication {
public:
	void run() {
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
	}

private:
	GLFWwindow* window;

	void process_input(GLFWwindow* window) {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
	}

	void initWindow() {
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(WIDTH, HEIGHT, "Hello Vulkan!", nullptr, nullptr);
	}

	void initVulkan() {

	}

	void mainLoop() {
		while (!glfwWindowShouldClose(window)) {
			process_input(window);
			glfwPollEvents();
		}
	}

	void cleanup() {
		glfwDestroyWindow(window);

		glfwTerminate();
	}
};