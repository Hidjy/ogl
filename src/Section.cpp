
#include "Section.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <iostream>

#include "Shader.hpp"

Section::Section() {
	glGenVertexArrays(1, &(this->_VAO));
	glGenBuffers(1, &(this->_VBO));
	// Bind our Vertex Array Object first, then bind and set our buffers and pointers.
	glBindVertexArray((this->_VAO));

	glBindBuffer(GL_ARRAY_BUFFER, (this->_VBO));
	//glBufferData(GL_ARRAY_BUFFER, sizeof(CubeRenderer::_vertices), CubeRenderer::_vertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	this->_pos = glm::vec3(0,0,0);
}

Section::Section(Section const &src) : _VAO(src.getVAO()), _VBO(src.getVBO()), _vertices(src.getVertices()), _pos(src.getPos()) {}

Section::~Section() {
	//TODO:Delete Buffers
}

GLuint					Section::getVAO() const {
	return this->_VAO;
}

GLuint					Section::getVBO() const {
	return this->_VBO;
}

std::vector<GLfloat>	Section::getVertices() const {
	return this->_vertices;
}

glm::vec3				Section::getPos() const {
	return this->_pos;
}


void Section::setPos(glm::vec3 pos) {
	this->_pos = pos;
}

static void multipush(std::vector<GLfloat> &target, std::vector<GLfloat> src)
{
	for (std::vector<GLfloat>::iterator it = src.begin(); it < src.end(); ++it) {
		target.push_back(*it);
	}
}

void Section::addQuad(glm::vec3 pos, int face) {

	if (face == 0) {
		multipush(this->_vertices, {0.5f + pos.x, -0.5f + pos.y, -0.5f + pos.z,  1.0f, 0.0f});
		multipush(this->_vertices, {0.5f + pos.x, 0.5f + pos.y,  -0.5f + pos.z,  1.0f, 1.0f});
		multipush(this->_vertices, {0.5f + pos.x, 0.5f + pos.y,  0.5f + pos.z,  0.0f, 1.0f});

		multipush(this->_vertices, {0.5f + pos.x,  0.5f + pos.y,  0.5f + pos.z,  0.0f, 1.0f});
		multipush(this->_vertices, {0.5f + pos.x, -0.5f + pos.y,  0.5f + pos.z,  0.0f, 0.0f});
		multipush(this->_vertices, {0.5f + pos.x, -0.5f + pos.y,  -0.5f + pos.z,  1.0f, 0.0f});
	}
	else if (face == 1) {
		multipush(this->_vertices, {-0.5f + pos.x, -0.5f + pos.y, -0.5f + pos.z,  0.0f, 0.0f});
		multipush(this->_vertices, {-0.5f + pos.x, 0.5f + pos.y,  0.5f + pos.z,  1.0f, 1.0f});
		multipush(this->_vertices, {-0.5f + pos.x, 0.5f + pos.y,  -0.5f + pos.z,  0.0f, 1.0f});

		multipush(this->_vertices, {-0.5f + pos.x,  0.5f + pos.y,  0.5f + pos.z,  1.0f, 1.0f});
		multipush(this->_vertices, {-0.5f + pos.x, -0.5f + pos.y,  -0.5f + pos.z, 0.0f, 0.0f});
		multipush(this->_vertices, {-0.5f + pos.x, -0.5f + pos.y,  0.5f + pos.z,  1.0f, 0.0f});
	}
	else if (face == 2) {
		multipush(this->_vertices, {-0.5f + pos.x, 0.5f + pos.y, -0.5f + pos.z,  0.0f, 0.0f});
		multipush(this->_vertices, {0.5f + pos.x, 0.5f + pos.y,  0.5f + pos.z,  1.0f, 1.0f});
		multipush(this->_vertices, {0.5f + pos.x, 0.5f + pos.y,  -0.5f + pos.z,  1.0f, 0.0f});

		multipush(this->_vertices, {0.5f + pos.x,  0.5f + pos.y,  0.5f + pos.z,  1.0f, 1.0f});
		multipush(this->_vertices, {-0.5f + pos.x, 0.5f + pos.y,  -0.5f + pos.z,  0.0f, 0.0f});
		multipush(this->_vertices, {-0.5f + pos.x, 0.5f + pos.y,  0.5f + pos.z,  0.0f, 1.0f});
	}
	else if (face == 3) {
		multipush(this->_vertices, {-0.5f + pos.x, -0.5f + pos.y, -0.5f + pos.z,  1.0f, 0.0f});
		multipush(this->_vertices, {0.5f + pos.x, -0.5f + pos.y,  -0.5f + pos.z,  0.0f, 0.0f});
		multipush(this->_vertices, {0.5f + pos.x, -0.5f + pos.y,  0.5f + pos.z,  0.0f, 1.0f});

		multipush(this->_vertices, {0.5f + pos.x,  -0.5f + pos.y,  0.5f + pos.z,  0.0f, 1.0f});
		multipush(this->_vertices, {-0.5f + pos.x, -0.5f + pos.y,  0.5f + pos.z,  1.0f, 1.0f});
		multipush(this->_vertices, {-0.5f + pos.x, -0.5f + pos.y,  -0.5f + pos.z, 1.0f, 0.0f});
	}
	else if (face == 4) {
		multipush(this->_vertices, {-0.5f + pos.x, -0.5f + pos.y, 0.5f + pos.z,  1.0f, 0.0f});
		multipush(this->_vertices, {0.5f + pos.x, -0.5f + pos.y,  0.5f + pos.z,  0.0f, 0.0f});
		multipush(this->_vertices, {0.5f + pos.x, 0.5f + pos.y,  0.5f + pos.z,  0.0f, 1.0f});

		multipush(this->_vertices, {0.5f + pos.x,  0.5f + pos.y, 0.5f + pos.z,  0.0f, 1.0f});
		multipush(this->_vertices, {-0.5f + pos.x, 0.5f + pos.y, 0.5f + pos.z,  1.0f, 1.0f});
		multipush(this->_vertices, {-0.5f + pos.x, -0.5f + pos.y, 0.5f + pos.z, 1.0f, 0.0f});
	}
	else if (face == 5) {
		multipush(this->_vertices, {-0.5f + pos.x, -0.5f + pos.y, -0.5f + pos.z,  1.0f, 0.0f});
		multipush(this->_vertices, {0.5f + pos.x, 0.5f + pos.y,  -0.5f + pos.z,  0.0f, 1.0f});
		multipush(this->_vertices, {0.5f + pos.x, -0.5f + pos.y,  -0.5f + pos.z,  0.0f, 0.0f});

		multipush(this->_vertices, {0.5f + pos.x,  0.5f + pos.y, -0.5f + pos.z,  0.0f, 1.0f});
		multipush(this->_vertices, {-0.5f + pos.x, -0.5f + pos.y, -0.5f + pos.z, 1.0f, 0.0f});
		multipush(this->_vertices, {-0.5f + pos.x, 0.5f + pos.y, -0.5f + pos.z,  1.0f, 1.0f});
	}
}

void	Section::generateMesh(int cubes[8][8][8]) {
	this->_vertices.clear();

	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			for (int z = 0; z < 8; z++) {
				int current = cubes[x][y][z];
				if (current != 0) {
					if (x == 0 or cubes[x - 1][y][z] == 0)
						this->addQuad(glm::vec3(x, y, z), 1);
					if (y == 0 or cubes[x][y - 1][z] == 0)
						this->addQuad(glm::vec3(x, y, z), 3);
					if (z == 0 or cubes[x][y][z - 1] == 0)
						this->addQuad(glm::vec3(x, y, z), 5);
					if (x == 7 or cubes[x + 1][y][z] == 0)
						this->addQuad(glm::vec3(x, y, z), 0);
					if (y == 7 or cubes[x][y + 1][z] == 0)
						this->addQuad(glm::vec3(x, y, z), 2);
					if (z == 7 or cubes[x][y][z + 1] == 0)
						this->addQuad(glm::vec3(x, y, z), 4);
				}
			}
		}
	}

	//Rebind Buffer
	glBindVertexArray((this->_VAO));
	glBindBuffer(GL_ARRAY_BUFFER, (this->_VBO));
	glBufferData(GL_ARRAY_BUFFER, this->_vertices.size() * sizeof(GLfloat), &(this->_vertices[0]), GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void	Section::render(Shader shader) {
	shader.Use();

	glm::mat4 model;
	model = glm::translate(model, this->_pos);
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(this->_VAO);
	glDrawArrays(GL_TRIANGLES, 0, this->_vertices.size() / 5);
	glBindVertexArray(0);
}

Section		&Section::operator=(Section const &src) {
	this->_VAO = src.getVAO();
	this->_VBO = src.getVBO();
	this->_vertices = src.getVertices();
	this->_pos = src.getPos();
	return *this;
}
