#pragma once

#include "Cube.hpp"
#include "Shader.hpp"
#include <glm/glm.hpp>
#include <vector>

class CubeRenderer {
private:
	GLuint	_VAO;
	GLuint	_VBO;

public:
	static GLfloat _vertices[180];

	CubeRenderer();
	~CubeRenderer();

void	render(Cube cube, Shader shader);
};
