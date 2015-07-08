#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"

#include <vector>

class Section {
private:
	GLuint	_VAO;
	GLuint	_VBO;

	std::vector<GLfloat>	_vertices;

	glm::vec3	_pos;

public:
	Section();
	~Section();

	void	setPos(glm::vec3 pos);

	void	addQuad(glm::vec3 pos, int face);
	void	generateMesh(int cubes[512]);
	void	render(Shader shader);
};
