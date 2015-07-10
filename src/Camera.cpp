#include "Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>

#include <GL/glew.h>

Camera::Camera(glm::vec3 p)
{
	pos = p;
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f,  0.0f);

	yaw = -90.0f;
	pitch = 0.0f;
	speed = 20.0f;

	Zoom = 45.0f;
}

void	Camera::ProcessKeyboard(enum Direction dir, GLfloat dt)
{
	switch (dir) {
		case UP:
			pos += dt * speed * up;
			break;
		case DOWN:
			pos -= dt * speed * up;
			break;
		case FORWARD:
			pos += dt * speed * front;
			break;
		case BACKWARD:
			pos -= dt * speed * front;
			break;
		case LEFT:
			pos -= glm::normalize(glm::cross(front, up)) * dt * speed;
			break;
		case RIGHT:
			pos += glm::normalize(glm::cross(front, up)) * dt * speed;
			break;
	}
}

void	Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset)
{
	GLfloat sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	this->yaw   += xoffset;
	this->pitch += yoffset;

	if(this->pitch > 89.0f)
		this->pitch = 89.0f;
	if(this->pitch < -89.0f)
		this->pitch = -89.0f;

	glm::vec3 tmp;
	tmp.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	tmp.y = sin(glm::radians(this->pitch));
	tmp.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front = glm::normalize(tmp);
}

glm::mat4	Camera::GetViewMatrix()
{
	glm::mat4 view;
	view = glm::lookAt(this->pos, this->pos + this->front, this->up);
	return view;
}
