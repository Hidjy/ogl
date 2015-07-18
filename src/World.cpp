#include "World.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Chunk.hpp"
#include "Shader.hpp"

#include <vector>

World::World() {
}

World::~World() {
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
}

void	World::renderNear(glm::vec3 pos, Shader shader) {
	for (size_t i = 0; i < _chunks.size(); i++) {
		glm::vec3 temp = glm::vec3(pos.x / CHUNK_SIZE + 0.5f, pos.y / CHUNK_SIZE + 0.5f, pos.z / CHUNK_SIZE + 0.5f) - _chunkPos[i];
		GLfloat distSqr = glm::dot(temp, temp);
		if (sqrt(distSqr) < 5)
			_chunks[i].render(shader);
	}
}
