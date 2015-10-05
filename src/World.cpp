#include "World.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Chunk.hpp"
#include "EWorld.hpp"
#include "ChunkManager.hpp"
#include "Block.hpp"
#include "Renderer.hpp"

# include <cmath>

World::World() {
}

World::~World() {
}

void	World::update(float dt) {
	_chunkManager.update(dt);
}

void	World::render(glm::vec3 pos, Renderer *renderer) {
	_chunkManager.setCamera(pos, glm::vec3(0, 0, 0)); //FIXME
	_chunkManager.render(renderer);
}


GLint	World::getWorldBlockId(float x, float y, float z) {
	try {
		// printf("chunk = {%d, %d, %d} = {%f, %f, %f}\n",
		// 	static_cast<int>(floor(x / Chunk::SIZE)),
		// 	static_cast<int>(floor(y / Chunk::SIZE)),
		// 	static_cast<int>(floor(z / Chunk::SIZE)),
		// 	x,
		// 	y,
		// 	z
		// );
		Chunk chunk = getChunk( floor(x / Chunk::SIZE), floor(y / Chunk::SIZE), floor(z / Chunk::SIZE));
		return chunk.getBlock(
			static_cast<int>(x) % Chunk::SIZE,
			static_cast<int>(y) % Chunk::SIZE,
			static_cast<int>(z) % Chunk::SIZE
		).getType();
	}
	catch (std::exception e) {
		// std::cout << "Pas de chunk" << std::endl;
		return -1;
	}
}

GLint	World::getWorldBlockId(glm::vec3 const &v) {
	return getWorldBlockId(v.x, v.y, v.z);
}

void	World::addChunk(Chunk *chunk) {
	_chunkManager.addChunk(chunk);
}


Chunk	&World::getChunk(int x, int y, int z) {
	return _chunkManager.getChunk(glm::vec3(x, y, z));
}
