#include "GUI.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "IUserInterface.hpp"
#include "InputManager.hpp"

#include <stdlib.h>

GUI	*GUI::_instance = nullptr;

GUI::GUI() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	_window = glfwCreateWindow(mode->width, mode->height, "OGL", monitor, nullptr);
	glfwMakeContextCurrent(_window);

	_windowWidth = mode->width;
	_windowHeight = mode->height;

	srand(1234);

	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;
	glewInit();

	glViewport(0, 0, _windowWidth, _windowHeight);

	_inputManager = new InputManager(_window);

	_time = 0.0f;
}

GUI::~GUI() {
	delete _inputManager;
}

GUI		*GUI::instance() {
	if (_instance == nullptr)
		_instance = new GUI();
	return _instance;
}

bool	GUI::shouldClose() {
	return glfwWindowShouldClose(_window);
}

int		GUI::getWindowWidth() {
	return _windowWidth;
}

int		GUI::getWindowHeigh() {
	return _windowHeight;
}

float	GUI::getAspectRatio() {
	return (static_cast<float>(_windowWidth) / static_cast<float>(_windowHeight));
}

void	GUI::doUpdate(IUserInterface &ui) {
	float newTime = glfwGetTime();
	_dt = _time - newTime;
	_time = newTime;

	glfwPollEvents();

	_inputManager->update(_dt);
	ui.update(_dt);
}

void	GUI::doRender(IUserInterface &ui) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ui.render();
	glfwSwapBuffers(_window);
}
