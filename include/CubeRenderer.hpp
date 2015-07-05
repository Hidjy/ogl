#pragma once

#include "Cube.hpp"
#include "Shader.hpp"

#include <vector>

class CubeRenderer {
public:
	static GLfloat vertices[6][20];

	glm::mat4 modelMatrix;
	GLuint VAO[6], VBO[6];

	CubeRenderer();
	~CubeRenderer();

	void	render(std::vector<Cube> cubes, Shader shader);
};
