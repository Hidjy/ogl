#include "Camera.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLEW_STATIC
#include <GL/glew.h>

Camera::Camera(glm::vec3 p)
{
	_pos = p;
	_front = glm::vec3(0.0f, 0.0f, 1.0f);
	_up = glm::vec3(0.0f, 1.0f,  0.0f);
	_left = glm::vec3(-1.0f, 0.0f,  0.0f);

	_zoom = 45.0f;
}

glm::mat4	Camera::getViewMatrix()
{
	glm::mat4 view = glm::lookAt(_pos, _pos + _front, _up);
	return view;
}
