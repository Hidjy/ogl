#include "InputManager.hpp"
#include "Camera.hpp"

bool		InputManager::_keys[1024];
GLfloat		InputManager::_lastX;
GLfloat		InputManager::_lastY;
bool		InputManager::_firstMouse = true;
Camera		*InputManager::_camera;

InputManager::InputManager(GLFWwindow* window, Camera *camera) {
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	_camera = camera;
}

InputManager::~InputManager() {
}

void	InputManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if(action == GLFW_PRESS)
			_keys[key] = true;
		else if(action == GLFW_RELEASE)
			_keys[key] = false;
	}
}

void	InputManager::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
}

void	InputManager::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if(_firstMouse)
	{
		_lastX = xpos;
		_lastY = ypos;
		_firstMouse = false;
	}

	GLfloat xoffset = xpos - _lastX;
	GLfloat yoffset = _lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	_lastX = xpos;
	_lastY = ypos;

	_camera->ProcessMouseMovement(xoffset, yoffset);
}

void	InputManager::update(GLfloat deltaTime) {
	if(_keys[GLFW_KEY_W])
		_camera->ProcessKeyboard(FORWARD, deltaTime);
	if(_keys[GLFW_KEY_S])
		_camera->ProcessKeyboard(BACKWARD, deltaTime);
	if(_keys[GLFW_KEY_A])
		_camera->ProcessKeyboard(LEFT, deltaTime);
	if(_keys[GLFW_KEY_D])
		_camera->ProcessKeyboard(RIGHT, deltaTime);
	if(_keys[GLFW_KEY_SPACE])
		_camera->ProcessKeyboard(UP, deltaTime);
	if(_keys[GLFW_KEY_LEFT_SHIFT])
		_camera->ProcessKeyboard(DOWN, deltaTime);
	if (_keys[GLFW_KEY_Q])
		_camera->ProcessKeyboard(BOOST_PLUS, deltaTime);
	if (_keys[GLFW_KEY_E])
		_camera->ProcessKeyboard(BOOST_MOINS, deltaTime);
}
