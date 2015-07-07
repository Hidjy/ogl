
#include "Section.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

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

Section::~Section() {
	//TODO:Delete Buffers
}

static void multipush(std::vector<GLfloat> &target, std::vector<GLfloat> src)
{
	for (std::vector<GLfloat>::iterator it = src.begin(); it < src.end(); ++it) {
		target.push_back(*it);
	}
}

void Section::addQuad(glm::vec3 pos) {

	multipush(this->_vertices, {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f});
	multipush(this->_vertices, {0.5f, -0.5f, -0.5f, 1.0f, 0.0f});
	multipush(this->_vertices, {0.5f, 0.5f, -0.5f, 1.0f, 1.0f});

	multipush(this->_vertices, {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f});
	multipush(this->_vertices, {-0.5f, 0.5f, -0.5f, 0.0f, 1.0f});
	multipush(this->_vertices, {0.5f, 0.5f, -0.5f, 1.0f, 1.0f});

}

void	Section::generateMesh(int cubes[512]) {
	this->_vertices.clear();

	this->addQuad(glm::vec3(0,0,0));

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
