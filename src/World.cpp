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
#include "ShaderManager.hpp"
#include "RenderContext.hpp"

#include "WorldGenerator.hpp"

# include <cmath>

World::World() {
	float (*perlinNoise)[GENERATOR_SIZE][GENERATOR_SIZE] = NULL;
	WorldGenerator::GenerateMap(&perlinNoise, 7);

	_blockTypeManager = new BlockTypeManager();
	_blockTypeManager->add("Stone", new BlockType());
	_blockTypeManager->add("Dirt", new BlockType());
	_blockTypeManager->add("Sand", new BlockType());
	_blockTypeManager->add("Water", new BlockType());

	_blockTypeManager[0]["Stone"]->setColor(Color(0.5f, 0.5f, 0.5f));
	_blockTypeManager[0]["Dirt"]->setColor(Color(0.5f, 0.25f, 0.0f));
	_blockTypeManager[0]["Sand"]->setColor(Color(0.75f, 0.75f, 0.0f));
	_blockTypeManager[0]["Water"]->setColor(Color(0.0f, 0.75f, 0.75f));

	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 2; y++) {
			for (int z = 0; z < 10; z++) {
				Chunk *chunk = new Chunk();
				chunk->setPos(glm::vec3(x, y, z));

				for (size_t x1 = 0; x1 < Chunk::SIZE; x1++) {
					for (size_t y1 = 0; y1 < Chunk::SIZE; y1++) {
						for (size_t z1 = 0; z1 < Chunk::SIZE; z1++) {
							std::string block_type("");
							if ((y1 + (y * Chunk::SIZE)) < ((*perlinNoise)[x1 + ((x ) * Chunk::SIZE)][z1 + ((z ) * Chunk::SIZE)] * static_cast<float>(Chunk::SIZE * 3.0f) - 32)) {
								if ((y1 + (y * Chunk::SIZE)) == 9)
									block_type = "Sand";
								else if (((y1 + (y * Chunk::SIZE)) + 5 < ((*perlinNoise)[x1 + ((x ) * Chunk::SIZE)][z1 + ((z ) * Chunk::SIZE)] * static_cast<float>(Chunk::SIZE * 3.0f) - 32)))
									block_type = "Stone";
								else
									block_type = "Dirt";
							}
							else if ((y1 + (y * Chunk::SIZE)) < 10)
								block_type = "Water";

							if (block_type != "") {
								chunk->getBlock(x1, y1, z1).setActive(true);
								chunk->getBlock(x1, y1, z1).setType(_blockTypeManager[0][block_type]);
							}
						}
					}
				}
				chunk->generateMesh();
				addChunk(chunk);
			}
		}
	}
}

World::~World() {
}

void	World::update(float dt) {
	_chunkManager.update(dt);
}

void	World::render(RenderContext *renderContext) {
	_chunkManager.render(renderContext);
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
		).getType() != nullptr; //FIXME: BlockType::getID() ?
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
