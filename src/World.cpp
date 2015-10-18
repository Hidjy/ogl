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
#include "IRenderContext.hpp"

#include "WorldGenerator.hpp"

#include "BlockTypeFactory.hpp"

# include <cmath>

World::World() {
	float (*perlinNoise)[GENERATOR_SIZE][GENERATOR_SIZE] = NULL;
	WorldGenerator::GenerateMap(&perlinNoise, 7);

	_blockTypeFactory = new BlockTypeFactory();

	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 2; y++) {
			for (int z = 0; z < 10; z++) {
				Chunk *chunk = new Chunk();
				chunk->setPos(glm::vec3(x, y, z));

				for (size_t x1 = 0; x1 < Chunk::SizeX; x1++) {
					for (size_t y1 = 0; y1 < Chunk::SizeY; y1++) {
						for (size_t z1 = 0; z1 < Chunk::SizeZ; z1++) {
							std::string block_type("");
							if ((y1 + (y * Chunk::SizeY)) < ((*perlinNoise)[x1 + ((x ) * Chunk::SizeX)][z1 + ((z ) * Chunk::SizeZ)] * static_cast<float>(Chunk::SizeY * 3.0f) - 32)) {
								if ((y1 + (y * Chunk::SizeY)) == 9)
									block_type = "Sand";
								else if (((y1 + (y * Chunk::SizeY)) + 5 < ((*perlinNoise)[x1 + ((x ) * Chunk::SizeX)][z1 + ((z ) * Chunk::SizeZ)] * static_cast<float>(Chunk::SizeY * 3.0f) - 32)))
									block_type = "Stone";
								else
									block_type = "Dirt";
							}
							else if ((y1 + (y * Chunk::SizeY)) < 10)
								block_type = "Water";

							if (block_type != "") {
								chunk->getBlock(x1, y1, z1).setActive(true);
								chunk->getBlock(x1, y1, z1).setType(_blockTypeFactory->create(block_type));
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

void	World::render(IRenderContext *renderContext) {
	_chunkManager.render(renderContext);
}


GLint	World::getWorldBlockId(float x, float y, float z) {
	int ix = static_cast<int>(x);
	int iy = static_cast<int>(y);
	int iz = static_cast<int>(z);
	try {
		Chunk &chunk = getChunk( ix >> Chunk::LogSizeX, iy >> Chunk::LogSizeY, iz >> Chunk::LogSizeZ);
		return chunk.getBlock(
			ix & Chunk::MaskX,
			iy & Chunk::MaskY,
			iz & Chunk::MaskZ
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
