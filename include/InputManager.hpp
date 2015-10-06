#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

enum Input {UP, DOWN, FORWARD, BACKWARD, LEFT, RIGHT, BOOST_PLUS, BOOST_MOINS};

class	Player;

class InputManager {
private:
	static bool			_keys[1024];
	static GLfloat		_lastX, _lastY;
	static bool			_firstMouse;

	static Player		*_player;

public:
	InputManager(GLFWwindow* window, Player *player);
	~InputManager();

	static void	key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void	scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void	mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void		update(GLfloat dt);
};
