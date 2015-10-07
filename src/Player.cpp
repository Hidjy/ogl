#include "Player.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "InputManager.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <string>
#include <GL/glew.h>

Player::Player(glm::vec3 p, World *w){
	_pos = p;
	_front = glm::vec3(0.0f, 0.0f, 1.0f);
	_up = glm::vec3(0.0f, 1.0f,  0.0f);
	_left = glm::normalize(glm::cross(_up, _front));

	_pitch = 0.0f;
	_yaw = 90.0f;

	_speed = 20.0f;

	Game::camera->_pos = _pos;
}

void	Player::move(Input input, GLfloat dt)
{
	switch (input) {
		case UP:
			if (Game::world->getWorldBlockId(Game::camera->_pos + (dt * _speed * Game::camera->_up)) == 0)
				_pos += _up * _speed * dt;
			break;
		case DOWN:
			if (Game::world->getWorldBlockId(Game::camera->_pos - (dt * _speed * Game::camera->_up)) == 0)
				_pos -= _up * _speed * dt;
			break;
		case FORWARD:
			if (Game::world->getWorldBlockId(Game::camera->_pos + (dt * _speed * Game::camera->_front)) == 0)
				_pos += _front * _speed * dt;
			break;
		case BACKWARD:
			if (Game::world->getWorldBlockId(Game::camera->_pos - (dt * _speed * Game::camera->_front)) == 0)
				_pos -= _front * _speed * dt;
			break;
		case LEFT:
			if (Game::world->getWorldBlockId(Game::camera->_pos - (glm::normalize(glm::cross(Game::camera->_front, Game::camera->_up)) * dt * _speed)) == 0)
				_pos += _left * _speed * dt;
			break;
		case RIGHT:
			if (Game::world->getWorldBlockId(Game::camera->_pos + (glm::normalize(glm::cross(Game::camera->_front, Game::camera->_up)) * dt * _speed)) == 0)
				_pos -= _left * _speed * dt;
			break;
		case BOOST_PLUS:
			_speed += 10.0f * dt;
			break;
		case BOOST_MOINS:
			_speed -= 10.0f * dt;
			break;
	}
	Game::camera->_pos = _pos;
}


void	Player::rotate(GLfloat xoffset, GLfloat yoffset)
{
	GLfloat sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	_yaw   += xoffset;
	_pitch += yoffset;

	if(_pitch > 89.0f)
		_pitch = 89.0f;
	if(_pitch < -89.0f)
		_pitch = -89.0f;

	glm::vec3 tmp;
	tmp.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	tmp.y = sin(glm::radians(_pitch));
	tmp.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_front = glm::normalize(tmp);

	_left = glm::normalize(glm::cross(_up, _front));

	Game::camera->_front = _front;
	Game::camera->_left= _left;
	Game::camera->_up = _up;
}
