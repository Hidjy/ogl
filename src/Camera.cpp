#include "Camera.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
	_pos = glm::vec3(10.0f, 20.0f, 10.0f);
	_front = glm::vec3(0.0f, 0.0f, 1.0f);
	_up = glm::vec3(0.0f, 1.0f,  0.0f);
	_left = glm::normalize(glm::cross(_up, _front));

	_zoom = 45.0f;
}

glm::mat4	Camera::getViewMatrix()
{
	glm::mat4 view = glm::lookAt(_pos, _pos + _front, _up);
	return view;
}
