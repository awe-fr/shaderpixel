#include "./../headers/WindowApp.hpp"

WindowApp::WindowApp() : _window(NULL) {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW." << std::endl;
		exit(1);
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->_window = glfwCreateWindow(WIDTH, HEIGHT, "shaderpixel", NULL, NULL);
	if (this->_window == NULL) {
		std::cerr << "Failed to open GLFW window." << std::endl;
		glfwTerminate();
		exit(1);
	}

	glfwMakeContextCurrent(this->_window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW." << std::endl;
		if (this->_window != NULL) {
			glfwDestroyWindow(this->_window);
		}
		glfwTerminate();
		exit(1);
	}

	glfwSetInputMode(this->_window, GLFW_STICKY_KEYS, GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(this->_window);
	glfwPollEvents();
}

WindowApp::~WindowApp() {
	if (this->_window != NULL) {
		glfwDestroyWindow(this->_window);
	}
	glfwTerminate();
}

bool WindowApp::isClosed() {
	if (glfwGetKey(this->_window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(this->_window) != 0) {
		return (true);
	}
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(this->_window);
	glfwPollEvents();
	return (false);
}