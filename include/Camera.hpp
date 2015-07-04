

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <string>

#include <GL/glew.h>

enum Direction {FORWARD, BACKWARD, LEFT, RIGHT};

class Camera
{
public:
	glm::vec3	pos;
	glm::vec3	front;
	glm::vec3	up;

	GLfloat		yaw;
	GLfloat		pitch;
	GLfloat		Zoom;

	Camera(glm::vec3 p);

	void	ProcessKeyboard(enum Direction dir, GLfloat dt);

	void	ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset);

	glm::mat4	GetViewMatrix();
};

#endif
