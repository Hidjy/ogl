#include "World.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Chunk.hpp"
#include "Shader.hpp"
#include <iostream>
#include <vector>

#include "EWorld.hpp"
# include <cmath>

World::World() {
}

World::~World() {
}

GLint	World::getWorldBlockId(float x, float y, float z) {
	try {
		printf("chunk = {%d, %d, %d} = {%f, %f, %f}\n",
			static_cast<int>(floor(x / CHUNK_SIZE)),
			static_cast<int>(floor(y / CHUNK_SIZE)),
			static_cast<int>(floor(z / CHUNK_SIZE)),
			x,
			y,
			z
		);
		Chunk chunk = getChuck( floor(x / CHUNK_SIZE), floor(y / CHUNK_SIZE), floor(z / CHUNK_SIZE));
		return chunk.getBlock(
			static_cast<int>(x) % CHUNK_SIZE,
			static_cast<int>(y) % CHUNK_SIZE,
			static_cast<int>(z) % CHUNK_SIZE
		);
	}
	catch (std::exception e) {
		std::cout << "Pas de chunck" << std::endl;
		return -1;
	}
}

void	World::add(Chunk const &chunk) {
	_chunkPos.push_back(chunk.getPos());
	_chunks.push_back(chunk);
}


Chunk	&World::getChuck(int x, int y, int z) {
	for (std::vector<Chunk>::iterator it = _chunks.begin() ; it != _chunks.end(); ++it) {
		if (it->getPos().x == x && it->getPos().y == y && it->getPos().z == z)
			return (*it);
	}
	throw EWorld("Pas de chunck");
}

void	World::renderNear(glm::vec3 pos, Shader shader) {
	for (size_t i = 0; i < _chunks.size(); i++) {
		glm::vec3 temp = glm::vec3(pos.x / CHUNK_SIZE + 0.5f, pos.y / CHUNK_SIZE + 0.5f, pos.z / CHUNK_SIZE + 0.5f) - _chunkPos[i];
		GLfloat distSqr = glm::dot(temp, temp);
		if (sqrt(distSqr) < 5)
			_chunks[i].render(shader);
	}
}
