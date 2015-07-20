#include "Camera.hpp"
#include "Player.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <GL/glew.h>

Player::Player(glm::vec3 p, World *w) : _camera(p){
	_pos = p;
	_speed = 20.0f;
	_world = w;

}

void	Player::ProcessKeyboard(enum Direction dir, GLfloat dt)
{
	switch (dir) {
		case UP:
			if (_world->getWorldBlockId(_camera._pos + (dt * _speed * _camera._up)) == 0)
				_camera._pos += dt * _speed * _camera._up;
			break;
		case DOWN:
			if (_world->getWorldBlockId(_camera._pos - (dt * _speed * _camera._up)) == 0)
				_camera._pos -= dt * _speed * _camera._up;
			break;
		case FORWARD:
			if (_world->getWorldBlockId(_camera._pos + (dt * _speed * _camera._front)) == 0)
				_camera._pos += dt * _speed * _camera._front;
			break;
		case BACKWARD:
			if (_world->getWorldBlockId(_camera._pos - (dt * _speed * _camera._front)) == 0)
				_camera._pos -= dt * _speed * _camera._front;
			break;
		case LEFT:
			if (_world->getWorldBlockId(_camera._pos - (glm::normalize(glm::cross(_camera._front, _camera._up)) * dt * _speed)) == 0)
				_camera._pos -= glm::normalize(glm::cross(_camera._front, _camera._up)) * dt * _speed;
			break;
		case RIGHT:
			if (_world->getWorldBlockId(_camera._pos + (glm::normalize(glm::cross(_camera._front, _camera._up)) * dt * _speed)) == 0)
				_camera._pos += glm::normalize(glm::cross(_camera._front, _camera._up)) * dt * _speed;
			break;
		case BOOST_PLUS:
			_speed++;
			break;
		case BOOST_MOINS:
			_speed--;
			break;
	}
}


void	Player::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset)
{
	GLfloat sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	_camera._yaw   += xoffset;
	_camera._pitch += yoffset;

	if(_camera._pitch > 89.0f)
		_camera._pitch = 89.0f;
	if(_camera._pitch < -89.0f)
		_camera._pitch = -89.0f;

	glm::vec3 tmp;
	tmp.x = cos(glm::radians(_camera._yaw)) * cos(glm::radians(_camera._pitch));
	tmp.y = sin(glm::radians(_camera._pitch));
	tmp.z = sin(glm::radians(_camera._yaw)) * cos(glm::radians(_camera._pitch));
	_camera._front = glm::normalize(tmp);
}

glm::mat4	Player::GetViewMatrix()
{
	glm::mat4 view = glm::lookAt(_camera._pos, _camera._pos + _camera._front, _camera._up);
	return view;
}
