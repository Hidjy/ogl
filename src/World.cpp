#include "World.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Chunk.hpp"
#include "EWorld.hpp"
#include "Player.hpp"
#include "ChunkManager.hpp"
#include "Block.hpp"
#include "ShaderManager.hpp"
#include "IRenderContext.hpp"

#include "WorldGenerator.hpp"

# include <cmath>

#include <iostream>

World::World() {

	_worldGenerator = new WorldGenerator();

	_chunkManager.setOrigin(-6, -1, -6);

	for (int x = 0; x < ChunkManager::SizeX; x++) {
		for (int y = 0; y < ChunkManager::SizeY; y++) {
			for (int z = 0; z < ChunkManager::SizeZ; z++) {
				Chunk *chunk = _chunkManager.getChunk(x, y, z);
				if (chunk == nullptr) {
					chunk = new Chunk();
					_chunkManager.setChunk(chunk, x, y, z);
				}
				_worldGenerator->generateChunk(chunk, x + _chunkManager.getX(), y +_chunkManager.getY(), z + _chunkManager.getZ());
			}
		}
	}
}

World::~World() {
}

void	World::update(float dt) {
	int px, py, pz;
	_player->getPos(px, py, pz);
	px = px >> Chunk::LogSizeX;
	py = py >> Chunk::LogSizeY;
	pz = pz >> Chunk::LogSizeZ;
	if (px < _chunkManager.getX() + ViewX or py < _chunkManager.getY() + ViewY or pz < _chunkManager.getZ() + ViewZ
			or px > _chunkManager.getX() + ChunkManager::SizeX - ViewX or py > _chunkManager.getY() + ChunkManager::SizeY - ViewY or pz > _chunkManager.getZ() + ChunkManager::SizeZ - ViewZ) {
		_chunkManager.setOrigin(px, py, pz);
	}
	_chunkManager.update(dt);
}

void	World::render(IRenderContext *renderContext) {
	_chunkManager.render(renderContext);
}


Block	*World::getBlock(int x, int y, int z) {
	Chunk *chunk = getChunk(
		x >> Chunk::LogSizeX,
		y >> Chunk::LogSizeY,
		z >> Chunk::LogSizeZ
	);
	if (chunk == nullptr)
		throw std::exception();
	return chunk->getBlock(
		x & Chunk::MaskX,
		y & Chunk::MaskY,
		z & Chunk::MaskZ
	);
}

Chunk	*World::getChunk(int x, int y, int z) {
	return _chunkManager.getChunk(x - _chunkManager.getX(), y - _chunkManager.getY(), z - _chunkManager.getZ());
}

void	World::setPlayer(Player *p) {
	_player = p;
}
