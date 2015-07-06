#pragma once

#include <glm/glm.hpp>

class Cube {
private:
	glm::vec3	_pos;

public:
	Cube(glm::vec3 pos);
	~Cube();

	glm::vec3	getPos();
};
