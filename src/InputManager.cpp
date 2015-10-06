#include "InputManager.hpp"
#include "Camera.hpp"
#include "Player.hpp"

bool		InputManager::_keys[1024];
GLfloat		InputManager::_lastX;
GLfloat		InputManager::_lastY;
bool		InputManager::_firstMouse = true;
Player		*InputManager::_player;

InputManager::InputManager(GLFWwindow* window, Player *player) {
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	_player = player;
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

	_player->rotate(xoffset, yoffset);
}

void	InputManager::update(GLfloat deltaTime) {
	if(_keys[GLFW_KEY_W])
		_player->move(FORWARD, deltaTime);
	if(_keys[GLFW_KEY_S])
		_player->move(BACKWARD, deltaTime);
	if(_keys[GLFW_KEY_A])
		_player->move(LEFT, deltaTime);
	if(_keys[GLFW_KEY_D])
		_player->move(RIGHT, deltaTime);
	if(_keys[GLFW_KEY_SPACE])
		_player->move(UP, deltaTime);
	if(_keys[GLFW_KEY_LEFT_SHIFT])
		_player->move(DOWN, deltaTime);
	if (_keys[GLFW_KEY_Q])
		_player->move(BOOST_PLUS, deltaTime);
	if (_keys[GLFW_KEY_E])
		_player->move(BOOST_MOINS, deltaTime);
}
