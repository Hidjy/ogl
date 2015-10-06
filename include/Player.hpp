#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <GL/glew.h>

#include "World.hpp"
#include "Camera.hpp"

#include "InputManager.hpp"

class	Player
{
private:
	glm::vec3	_pos;

	glm::vec3	_front;
	glm::vec3	_left;
	glm::vec3	_up;

	GLfloat		_speed;

public:
	Player(glm::vec3 p, World *w);
	void	move(Input input, GLfloat dt);
	void	rotate(GLfloat xoffset, GLfloat yoffset);
	//TODO: update();
	//TODO: render();
};
