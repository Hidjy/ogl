#include "CubeRenderer.hpp"
#include "Cube.hpp"
#include "Shader.hpp"

#include <vector>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLfloat CubeRenderer::vertices[6][20] = {
	//TOP
	{
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	},

	//NORTH
	{
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	},

	//WEST
	{
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	},

	//EAST
	{
		0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	},

	//SOUTH
	{
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	},

	//BOTTOM
	{
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
	}
};

#define FACES 1

CubeRenderer::CubeRenderer(Cube &cube) {

	glm::mat4 model;
	model = glm::translate(model, cube.pos);
	this->modelMatrix = model;

	for (size_t i = 0; i < FACES; i++) {
		glGenVertexArrays(1, &(this->VAO[i]));
		glGenBuffers(1, &(this->VBO[i]));

		glBindVertexArray(this->VAO[i]);

		glBindBuffer(GL_ARRAY_BUFFER, this->VBO[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(CubeRenderer::vertices[i]), CubeRenderer::vertices[i], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
	}
}

CubeRenderer::~CubeRenderer() {
	glDeleteVertexArrays(FACES, VAO);
	glDeleteBuffers(FACES, VBO);
}

void	CubeRenderer::render(std::vector<Cube> cubes, Shader shader)
{
	for (size_t i = 0; i < FACES; i++) {

		glBindVertexArray(this->VAO[i]);

		for (std::vector<Cube>::iterator cube = cubes.begin(); cube < cubes.end(); ++cube) {
				glm::mat4 model;
				model = glm::translate(model, cube->pos);

				glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));

				glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		}
		glBindVertexArray(0);

	}
}
