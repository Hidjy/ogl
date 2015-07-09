#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"

#include <vector>

#define SECTION_SIZE 32 // !!! Must be a divisor of CHUNK_SIZE (see Chunk.hpp)

class Section {
private:
	GLuint	_VAO;
	GLuint	_VBO;

	std::vector<GLfloat>	_vertices;

	glm::vec3	_pos;

public:
	Section();
	Section(Section const &src);
	~Section();

	GLuint					getVAO() const;
	GLuint					getVBO() const;
	std::vector<GLfloat>	getVertices() const;
	glm::vec3				getPos() const;

	void		setPos(glm::vec3 pos);

	void		addQuad(glm::vec3 pos, int face);
	void		generateMesh(int cubes[SECTION_SIZE][SECTION_SIZE][SECTION_SIZE]);
	void		render(Shader shader);

	Section		&operator=(Section const &src);
};
