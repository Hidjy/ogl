

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <string>

#include <GL/glew.h>

#define CAMERA_SPEED 20

enum Direction {UP, DOWN, FORWARD, BACKWARD, LEFT, RIGHT};

class Camera
{
public:
	glm::vec3	_pos;
	glm::vec3	_front;
	glm::vec3	_up;

	GLfloat		_yaw;
	GLfloat		_pitch;
	GLfloat		_zoom;

	GLfloat		_speed;

	Camera(glm::vec3 p);

	void	ProcessKeyboard(enum Direction dir, GLfloat dt);

	void	ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset);

	glm::mat4	GetViewMatrix();
};

#endif
