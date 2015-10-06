
#include "ChunkRenderer.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <iostream>

#include "Shader.hpp"
#include "Chunk.hpp"
#include "Block.hpp"
#include "Renderer.hpp"

ChunkRenderer::ChunkRenderer() {
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

ChunkRenderer::ChunkRenderer(ChunkRenderer const &src) : _VAO(src.getVAO()), _VBO(src.getVBO()), _vertices(src.getVertices()), _pos(src.getPos()) {}

ChunkRenderer::~ChunkRenderer() {
	//TODO:Delete Buffers
}

GLuint					ChunkRenderer::getVAO() const {
	return _VAO;
}

GLuint					ChunkRenderer::getVBO() const {
	return _VBO;
}

std::vector<GLfloat>	ChunkRenderer::getVertices() const {
	return _vertices;
}

glm::vec3				ChunkRenderer::getPos() const {
	return _pos;
}


void ChunkRenderer::setPos(glm::vec3 pos) {
	_pos = pos;
}

static void multipush(std::vector<GLfloat> &target, std::vector<GLfloat> src)
{
	for (std::vector<GLfloat>::iterator it = src.begin(); it < src.end(); ++it) {
		target.push_back(*it);
	}
}

void ChunkRenderer::addQuad(Block block, glm::vec3 pos, int face) {
	// float layer = static_cast<float>( textureManager.getTexturePos(block.getType(), face) );
	float layer = static_cast<float>( block.getType() );
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

void	ChunkRenderer::generateMesh(Block ***blocks) {
	_vertices.clear();

	for (int x = 0; x < Chunk::SIZE; x++) {
		for (int y = 0; y < Chunk::SIZE; y++) {
			for (int z = 0; z < Chunk::SIZE; z++) {
				Block current = blocks[x][y][z];
				if (current.isActive()) {
					if (x == 0 or blocks[x - 1][y][z].isActive() == false)
						addQuad(current, glm::vec3(x, y, z), 1);
					if (y == 0 or blocks[x][y - 1][z].isActive() == false)
						addQuad(current, glm::vec3(x, y, z), 3);
					if (z == 0 or blocks[x][y][z - 1].isActive() == false)
						addQuad(current, glm::vec3(x, y, z), 5);
					if (x == Chunk::SIZE - 1 or blocks[x + 1][y][z].isActive() == false)
						addQuad(current, glm::vec3(x, y, z), 0);
					if (y == Chunk::SIZE - 1 or blocks[x][y + 1][z].isActive() == false)
						addQuad(current, glm::vec3(x, y, z), 2);
					if (z == Chunk::SIZE - 1 or blocks[x][y][z + 1].isActive() == false)
						addQuad(current, glm::vec3(x, y, z), 4);
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

void	ChunkRenderer::render(Renderer *renderer) {
	glBindVertexArray(_VAO);
	glDrawArrays(GL_TRIANGLES, 0, _vertices.size() / 6);
	glBindVertexArray(0);
}

ChunkRenderer		&ChunkRenderer::operator=(ChunkRenderer const &src) {
	_VAO = src.getVAO();
	_VBO = src.getVBO();
	_vertices = src.getVertices();
	_pos = src.getPos();
	return *this;
}
