#include "Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>

#include <GL/glew.h>

Camera::Camera(glm::vec3 p)
{
	this->pos = p;
	this->front = glm::vec3(0.0f, 0.0f, -1.0f);
	this->up = glm::vec3(0.0f, 1.0f,  0.0f);

	this->yaw = -90.0f;
	this->pitch = 0.0f;

	this->Zoom = 45.0f;
}

void	Camera::ProcessKeyboard(enum Direction dir, GLfloat dt)
{
	GLfloat cameraSpeed = CAMERA_SPEED * dt;
	if(dir == UP)
		this->pos += cameraSpeed * this->up;
	if(dir == DOWN)
		this->pos -= cameraSpeed * this->up;
	if(dir == FORWARD)
		this->pos += cameraSpeed * this->front;
	if(dir == BACKWARD)
		this->pos -= cameraSpeed * this->front;
	if(dir == LEFT)
		this->pos -= glm::normalize(glm::cross(this->front, this->up)) * cameraSpeed;
	if(dir == RIGHT)
		this->pos += glm::normalize(glm::cross(this->front, this->up)) * cameraSpeed;
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
