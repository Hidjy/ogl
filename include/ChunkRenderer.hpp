#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "Shader.hpp"
#include "Block.hpp"
#include "Renderer.hpp"

#include <vector>

class ChunkRenderer {
private:
	GLuint	_VAO;
	GLuint	_VBO;

	std::vector<GLfloat>	_vertices;

public:
	ChunkRenderer();
	ChunkRenderer(ChunkRenderer const &src);
	~ChunkRenderer();

	GLuint					getVAO() const;
	GLuint					getVBO() const;
	std::vector<GLfloat>	getVertices() const;

	void		generateMesh(Block ***blocks);
	void		render(Renderer *renderer);

	ChunkRenderer		&operator=(ChunkRenderer const &src);
};
