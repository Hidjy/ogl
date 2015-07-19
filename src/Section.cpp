
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
	glGenVertexArrays(1, &(_VAO));
	glGenBuffers(1, &(_VBO));
	// Bind our Vertex Array Object first, then bind and set our buffers and pointers.
	glBindVertexArray((_VAO));

	glBindBuffer(GL_ARRAY_BUFFER, (_VBO));
	//glBufferData(GL_ARRAY_BUFFER, sizeof(CubeRenderer::_vertices), CubeRenderer::_vertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	_pos = glm::vec3(0,0,0);
}

Section::Section(Section const &src) : _VAO(src.getVAO()), _VBO(src.getVBO()), _vertices(src.getVertices()), _pos(src.getPos()) {}

Section::~Section() {
	//TODO:Delete Buffers
}

GLuint					Section::getVAO() const {
	return _VAO;
}

GLuint					Section::getVBO() const {
	return _VBO;
}

std::vector<GLfloat>	Section::getVertices() const {
	return _vertices;
}

glm::vec3				Section::getPos() const {
	return _pos;
}


void Section::setPos(glm::vec3 pos) {
	_pos = pos;
}

static void multipush(std::vector<GLfloat> &target, std::vector<GLfloat> src)
{
	for (std::vector<GLfloat>::iterator it = src.begin(); it < src.end(); ++it) {
		target.push_back(*it);
	}
}

void Section::addQuad(TextureManager &tm, int block, glm::vec3 pos, int face) {
	float layer = static_cast<float>( tm.getTexturePos(block, face) );
	if (face == 0) {
		multipush(_vertices, {0.5f + pos.x, -0.5f + pos.y, -0.5f + pos.z,  1.0f, 0.0f, layer});
		multipush(_vertices, {0.5f + pos.x, 0.5f + pos.y,  -0.5f + pos.z,  1.0f, 1.0f, layer});
		multipush(_vertices, {0.5f + pos.x, 0.5f + pos.y,  0.5f + pos.z,  0.0f, 1.0f, layer});

		multipush(_vertices, {0.5f + pos.x,  0.5f + pos.y,  0.5f + pos.z,  0.0f, 1.0f, layer});
		multipush(_vertices, {0.5f + pos.x, -0.5f + pos.y,  0.5f + pos.z,  0.0f, 0.0f, layer});
		multipush(_vertices, {0.5f + pos.x, -0.5f + pos.y,  -0.5f + pos.z,  1.0f, 0.0f, layer});
	}
	else if (face == 1) {
		multipush(_vertices, {-0.5f + pos.x, -0.5f + pos.y, -0.5f + pos.z,  0.0f, 0.0f, layer});
		multipush(_vertices, {-0.5f + pos.x, 0.5f + pos.y,  0.5f + pos.z,  1.0f, 1.0f, layer});
		multipush(_vertices, {-0.5f + pos.x, 0.5f + pos.y,  -0.5f + pos.z,  0.0f, 1.0f, layer});

		multipush(_vertices, {-0.5f + pos.x,  0.5f + pos.y,  0.5f + pos.z,  1.0f, 1.0f, layer});
		multipush(_vertices, {-0.5f + pos.x, -0.5f + pos.y,  -0.5f + pos.z, 0.0f, 0.0f, layer});
		multipush(_vertices, {-0.5f + pos.x, -0.5f + pos.y,  0.5f + pos.z,  1.0f, 0.0f, layer});
	}
	else if (face == 2) {
		multipush(_vertices, {-0.5f + pos.x, 0.5f + pos.y, -0.5f + pos.z,  1.0f, 0.0f, layer});
		multipush(_vertices, {0.5f + pos.x, 0.5f + pos.y,  0.5f + pos.z,  0.0f, 1.0f, layer});
		multipush(_vertices, {0.5f + pos.x, 0.5f + pos.y,  -0.5f + pos.z,  0.0f, 0.0f, layer});

		multipush(_vertices, {0.5f + pos.x,  0.5f + pos.y,  0.5f + pos.z,  0.0f, 1.0f, layer});
		multipush(_vertices, {-0.5f + pos.x, 0.5f + pos.y,  -0.5f + pos.z,  1.0f, 0.0f, layer});
		multipush(_vertices, {-0.5f + pos.x, 0.5f + pos.y,  0.5f + pos.z,  1.0f, 1.0f, layer});
	}
	else if (face == 3) {
		multipush(_vertices, {-0.5f + pos.x, -0.5f + pos.y, -0.5f + pos.z,  1.0f, 0.0f, layer});
		multipush(_vertices, {0.5f + pos.x, -0.5f + pos.y,  -0.5f + pos.z,  0.0f, 0.0f, layer});
		multipush(_vertices, {0.5f + pos.x, -0.5f + pos.y,  0.5f + pos.z,  0.0f, 1.0f, layer});

		multipush(_vertices, {0.5f + pos.x,  -0.5f + pos.y,  0.5f + pos.z,  0.0f, 1.0f, layer});
		multipush(_vertices, {-0.5f + pos.x, -0.5f + pos.y,  0.5f + pos.z,  1.0f, 1.0f, layer});
		multipush(_vertices, {-0.5f + pos.x, -0.5f + pos.y,  -0.5f + pos.z, 1.0f, 0.0f, layer});
	}
	else if (face == 4) {
		multipush(_vertices, {-0.5f + pos.x, -0.5f + pos.y, 0.5f + pos.z,  0.0f, 0.0f, layer});
		multipush(_vertices, {0.5f + pos.x, -0.5f + pos.y,  0.5f + pos.z,  1.0f, 0.0f, layer});
		multipush(_vertices, {0.5f + pos.x, 0.5f + pos.y,  0.5f + pos.z,  1.0f, 1.0f, layer});

		multipush(_vertices, {0.5f + pos.x,  0.5f + pos.y, 0.5f + pos.z,  1.0f, 1.0f, layer});
		multipush(_vertices, {-0.5f + pos.x, 0.5f + pos.y, 0.5f + pos.z,  0.0f, 1.0f, layer});
		multipush(_vertices, {-0.5f + pos.x, -0.5f + pos.y, 0.5f + pos.z, 0.0f, 0.0f, layer});
	}
	else if (face == 5) {
		multipush(_vertices, {-0.5f + pos.x, -0.5f + pos.y, -0.5f + pos.z,  1.0f, 0.0f, layer});
		multipush(_vertices, {0.5f + pos.x, 0.5f + pos.y,  -0.5f + pos.z,  0.0f, 1.0f, layer});
		multipush(_vertices, {0.5f + pos.x, -0.5f + pos.y,  -0.5f + pos.z,  0.0f, 0.0f, layer});

		multipush(_vertices, {0.5f + pos.x,  0.5f + pos.y, -0.5f + pos.z,  0.0f, 1.0f, layer});
		multipush(_vertices, {-0.5f + pos.x, -0.5f + pos.y, -0.5f + pos.z, 1.0f, 0.0f, layer});
		multipush(_vertices, {-0.5f + pos.x, 0.5f + pos.y, -0.5f + pos.z,  1.0f, 1.0f, layer});
	}
}

void	Section::generateMesh(TextureManager &tm, int cubes[SECTION_SIZE][SECTION_SIZE][SECTION_SIZE]) {
	_vertices.clear();

	for (int x = 0; x < SECTION_SIZE; x++) {
		for (int y = 0; y < SECTION_SIZE; y++) {
			for (int z = 0; z < SECTION_SIZE; z++) {
				int current = cubes[x][y][z];
				if (current != 0) {
					if (x == 0 or cubes[x - 1][y][z] == 0)
						addQuad(tm, current, glm::vec3(x, y, z), 1);
					if (y == 0 or cubes[x][y - 1][z] == 0)
						addQuad(tm, current, glm::vec3(x, y, z), 3);
					if (z == 0 or cubes[x][y][z - 1] == 0)
						addQuad(tm, current, glm::vec3(x, y, z), 5);
					if (x == SECTION_SIZE - 1 or cubes[x + 1][y][z] == 0)
						addQuad(tm, current, glm::vec3(x, y, z), 0);
					if (y == SECTION_SIZE - 1 or cubes[x][y + 1][z] == 0)
						addQuad(tm, current, glm::vec3(x, y, z), 2);
					if (z == SECTION_SIZE - 1 or cubes[x][y][z + 1] == 0)
						addQuad(tm, current, glm::vec3(x, y, z), 4);
				}
			}
		}
	}

	//Rebind Buffer
	glBindVertexArray((_VAO));
	glBindBuffer(GL_ARRAY_BUFFER, (_VBO));
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(GLfloat), &(_vertices[0]), GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void	Section::render(Shader shader) {
	shader.Use();

	glm::mat4 model;
	model = glm::translate(model, _pos);
	glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(_VAO);
	glDrawArrays(GL_TRIANGLES, 0, _vertices.size() / 5);
	glBindVertexArray(0);
}

Section		&Section::operator=(Section const &src) {
	_VAO = src.getVAO();
	_VBO = src.getVBO();
	_vertices = src.getVertices();
	_pos = src.getPos();
	return *this;
}
