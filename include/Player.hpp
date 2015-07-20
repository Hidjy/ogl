#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <SOIL/SOIL.h>

#include <GL/glew.h>

#include "World.hpp"
#include "Camera.hpp"


class	Player
{
public:
	glm::vec3	_pos;
	Camera		_camera;
	World		*_world;
	GLfloat		_speed;

	Player(glm::vec3 p, World *w);
	void	ProcessKeyboard(enum Direction dir, GLfloat dt);
	void	ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset);
	glm::mat4	GetViewMatrix();

};
