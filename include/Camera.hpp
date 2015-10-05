#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <GL/glew.h>

#define CAMERA_SPEED 20

enum Direction {UP, DOWN, FORWARD, BACKWARD, LEFT, RIGHT, BOOST_PLUS, BOOST_MOINS};

class Camera
{
public:
	glm::vec3	_pos;
	glm::vec3	_front;
	glm::vec3	_up;

	GLfloat		_yaw;
	GLfloat		_pitch;
	GLfloat		_zoom;

	Camera(glm::vec3 p);

	glm::mat4	getViewMatrix();

};
