#include "Cube.hpp"
#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>

Cube::Cube() {
	this->_pos = glm::vec3(0, 0, 0);
	this->_type = 0;
}

Cube::Cube(Cube const &src) : _pos(src.getPos()), _type(src.getType()){
}

Cube::Cube(glm::vec3 pos, int type) : _pos(pos), _type(type) {
}

Cube::~Cube() {
}

glm::vec3	Cube::getPos() const {
	return this->_pos;
}

int			Cube::getType() const {
	return this->_type;
}

Cube		&Cube::operator=(Cube const &src) {
	this->_pos = src.getPos();
	this->_type = src.getType();
	return *this;
}
