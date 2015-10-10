#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#define CAMERA_SPEED 20

class Camera
{
public:
	glm::vec3	_pos;

	glm::vec3	_front;
	glm::vec3	_up;
	glm::vec3	_left;

	GLfloat		_zoom;

	Camera();

	glm::mat4	getViewMatrix();

};
