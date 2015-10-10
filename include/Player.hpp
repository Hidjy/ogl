#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

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

	GLfloat		_pitch;
	GLfloat		_yaw;

	GLfloat		_speed;

	World		*_world;
	Camera		*_camera;

public:
	Player();

	void	setWorld(World *w);
	void	setCamera(Camera *c);

	void	move(Input input, GLfloat dt);
	void	rotate(GLfloat xoffset, GLfloat yoffset);
	void	update(float dt);
	//TODO: render();
};
