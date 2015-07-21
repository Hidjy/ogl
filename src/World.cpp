#include "World.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Chunk.hpp"
#include "Shader.hpp"
#include <iostream>
#include <vector>

#include "EWorld.hpp"
# include <cmath>

#include "Block.hpp"

World::World() {
}

World::~World() {
}

GLint	World::getWorldBlockId(float x, float y, float z) {
	try {
		printf("chunk = {%d, %d, %d} = {%f, %f, %f}\n",
			static_cast<int>(floor(x / Chunk::SIZE)),
			static_cast<int>(floor(y / Chunk::SIZE)),
			static_cast<int>(floor(z / Chunk::SIZE)),
			x,
			y,
			z
		);
		Chunk chunk = getChuck( floor(x / Chunk::SIZE), floor(y / Chunk::SIZE), floor(z / Chunk::SIZE));
		return chunk.getBlock(
			static_cast<int>(x) % Chunk::SIZE,
			static_cast<int>(y) % Chunk::SIZE,
			static_cast<int>(z) % Chunk::SIZE
		).getType();
	}
	catch (std::exception e) {
		std::cout << "Pas de chunk" << std::endl;
		return -1;
	}
}

GLint	World::getWorldBlockId(glm::vec3 const &v) {
	return getWorldBlockId(v.x, v.y, v.z);
}

void	World::add(Chunk *chunk) {
	_chunks.push_back(chunk);
}


Chunk	&World::getChuck(int x, int y, int z) {
	for (std::vector<Chunk *>::iterator it = _chunks.begin() ; it != _chunks.end(); ++it) {
		glm::vec3 pos = (**it).getPos();
		if (pos.x == x && pos.y == y && pos.z == z)
			return (**it);
	}
	throw EWorld("No Chunk.");
}

void	World::renderNear(glm::vec3 pos, Shader shader) {
	for (size_t i = 0; i < _chunks.size(); i++) {
		glm::vec3 temp = glm::vec3(pos.x / Chunk::SIZE + 0.5f, pos.y / Chunk::SIZE + 0.5f, pos.z / Chunk::SIZE + 0.5f) - _chunks[i]->getPos();
		GLfloat distSqr = glm::dot(temp, temp);
		if (sqrt(distSqr) < 5)
			_chunks[i]->render(shader);
	}
}
