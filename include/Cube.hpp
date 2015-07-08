#pragma once

#include <glm/glm.hpp>

class Cube {
private:
	glm::vec3	_pos;
	int			_type;

public:
	Cube();
	Cube(Cube const &src);
	Cube(glm::vec3 pos, int type);
	~Cube();

	glm::vec3	getPos() const;
	int			getType() const;

	Cube	&operator=(Cube const &src);
};
