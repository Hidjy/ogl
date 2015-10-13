#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "IInputReceiver.hpp"

#include <vector>
#include <string>

enum Input {UP, DOWN, FORWARD, BACKWARD, LEFT, RIGHT, BOOST_PLUS, BOOST_MOINS};

class InputManager {
private:
	static bool			_keys[1024];
	static GLfloat		_lastX, _lastY;
	static bool			_firstMouse;

	static std::vector<IInputReceiver *> _mouseCallbackList;

public:
	InputManager(GLFWwindow* window);
	~InputManager();

	static void	key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void	scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void	mouse_callback(GLFWwindow* window, double xpos, double ypos);

	static void	addCallback(std::string name, IInputReceiver *ir);

	static bool isKeyDown(int key);
	static void getMousePos(GLfloat &x, GLfloat &y);

	void		update(GLfloat dt);
};
