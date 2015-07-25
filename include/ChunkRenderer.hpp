#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"
#include "Block.hpp"
#include "Renderer.hpp"

#include <vector>

class ChunkRenderer {
private:
	GLuint	_VAO;
	GLuint	_VBO;

	std::vector<GLfloat>	_vertices;

	glm::vec3	_pos;

public:
	ChunkRenderer();
	ChunkRenderer(ChunkRenderer const &src);
	~ChunkRenderer();

	GLuint					getVAO() const;
	GLuint					getVBO() const;
	std::vector<GLfloat>	getVertices() const;
	glm::vec3				getPos() const;

	void		setPos(glm::vec3 pos);

	void		addQuad(Block block, glm::vec3 pos, int face);
	void		generateMesh(Block ***blocks);
	void		render(Renderer *renderer);

	ChunkRenderer		&operator=(ChunkRenderer const &src);
};
