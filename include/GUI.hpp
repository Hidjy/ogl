#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "IUserInterface.hpp"

#include "InputManager.hpp"

#include "RenderContext.hpp"

class GUI {
private:
	static GUI	*_instance;

	GLFWwindow*	_window;

	int		_windowWidth;
	int		_windowHeight;

	float	_dt;
	float	_time;

	InputManager	*_inputManager;

	GUI();
	~GUI();

public:
	static GUI		*instance();

	bool	shouldClose();

	int		getWindowWidth();
	int		getWindowHeigh();

	float	getAspectRatio();

	void	doUpdate(IUserInterface &ui);
	void	doRender(IUserInterface &ui);
};
