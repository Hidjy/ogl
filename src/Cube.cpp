#include "Cube.hpp"
#include <glm/glm.hpp>

Cube::Cube(glm::vec3 pos) : _pos(pos) {
}

Cube::~Cube() {
}

glm::vec3 Cube::getPos() {
	return this->_pos;
}
