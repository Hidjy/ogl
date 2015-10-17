#include "Player.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "InputManager.hpp"
#include "IInputReceiver.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <string>

Player::Player(){
	_pos = glm::vec3(10.0f, 20.0f, 10.0f);
	_front = glm::vec3(0.0f, 0.0f, 1.0f);
	_up = glm::vec3(0.0f, 1.0f,  0.0f);
	_left = glm::normalize(glm::cross(_up, _front));

	_pitch = 0.0f;
	_yaw = 90.0f;

	_speed = 20.0f;

	_camera = nullptr;
	_world = nullptr;

	InputManager::addCallback("MouseMove", this);
}

Player::~Player() {
}

void	Player::setWorld(World *w) {
	_world = w;
}

void	Player::setCamera(Camera *c) {
	_camera = c;
}

void	Player::update(float dt) {
	if(InputManager::isKeyDown(GLFW_KEY_W))
		move(FORWARD, dt);
	if(InputManager::isKeyDown(GLFW_KEY_S))
		move(BACKWARD, dt);
	if(InputManager::isKeyDown(GLFW_KEY_A))
		move(LEFT, dt);
	if(InputManager::isKeyDown(GLFW_KEY_D))
		move(RIGHT, dt);
	if(InputManager::isKeyDown(GLFW_KEY_SPACE))
		move(UP, dt);
	if(InputManager::isKeyDown(GLFW_KEY_LEFT_SHIFT))
		move(DOWN, dt);
	if (InputManager::isKeyDown(GLFW_KEY_Q))
		move(BOOST_PLUS, dt);
	if (InputManager::isKeyDown(GLFW_KEY_E))
		move(BOOST_MOINS, dt);
}

void	Player::move(Input input, GLfloat dt)
{
	switch (input) {
		case UP:
			if (_world->getWorldBlockId(_camera->_pos + (dt * _speed * _camera->_up)) == 0)
				_pos += _up * _speed * dt;
			break;
		case DOWN:
			if (_world->getWorldBlockId(_camera->_pos - (dt * _speed * _camera->_up)) == 0)
				_pos -= _up * _speed * dt;
			break;
		case FORWARD:
			if (_world->getWorldBlockId(_camera->_pos + (dt * _speed * _camera->_front)) == 0)
				_pos += _front * _speed * dt;
			break;
		case BACKWARD:
			if (_world->getWorldBlockId(_camera->_pos - (dt * _speed * _camera->_front)) == 0)
				_pos -= _front * _speed * dt;
			break;
		case LEFT:
			if (_world->getWorldBlockId(_camera->_pos - (glm::normalize(glm::cross(_camera->_front, _camera->_up)) * dt * _speed)) == 0)
				_pos += _left * _speed * dt;
			break;
		case RIGHT:
			if (_world->getWorldBlockId(_camera->_pos + (glm::normalize(glm::cross(_camera->_front, _camera->_up)) * dt * _speed)) == 0)
				_pos -= _left * _speed * dt;
			break;
		case BOOST_PLUS:
			_speed += 10.0f * dt;
			break;
		case BOOST_MOINS:
			_speed -= 10.0f * dt;
			break;
	}
	_camera->_pos = _pos;
}


void	Player::onMouseMove(GLfloat xoffset, GLfloat yoffset)
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

	_camera->_front = _front;
	_camera->_left= _left;
	_camera->_up = _up;
}
