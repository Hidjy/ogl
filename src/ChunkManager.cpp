#include "ChunkManager.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Game.hpp"
#include "Chunk.hpp"
#include "ShaderManager.hpp"
#include "IRenderContext.hpp"

#include <exception>
#include <utility>

ChunkManager::ChunkManager() {
	_x = 0;
	_y = 0;
	_z = 0;

	_chunks = new Chunk***[SizeX];
	for (int x = 0; x < SizeX; x++) {
		_chunks[x] = new Chunk**[SizeY];
		for (int y = 0; y < SizeY; y++) {
			_chunks[x][y] = new Chunk*[SizeZ];
			for (int z = 0; z < SizeZ; z++)
				_chunks[x][y][z] = nullptr;
		}
	}
}

ChunkManager::~ChunkManager() {
	for (int x = 0; x < SizeX; x++) {
		for (int y = 0; y < SizeY; y++) {
			for (int z = 0; z < SizeZ; z++) {
				if (_chunks[x][y][z] != nullptr)
					delete _chunks[x][y][z];
			}
			delete [] _chunks[x][y];
		}
		delete [] _chunks[x];
	}
	delete [] _chunks;
}

void ChunkManager::update(float dt)
{
	updateAsyncChunker();

	updateSetupQueue();
	updateRebuildQueue();
	updateUnloadQueue();

	// updateChunkList();
}

void	ChunkManager::render(IRenderContext *renderContext) {
	renderContext->getShaderManager()->getShader("Chunk")->use();

	for (int x = 0; x < SizeX; x++) {
		for (int y = 0; y < SizeY; y++) {
			for (int z = 0; z < SizeZ; z++) {
				if (_chunks[x][y][z] != nullptr) {
					if (_chunks[x][y][z]->isSetup()) {
						glm::mat4 MVP;
						MVP = glm::translate(MVP, glm::vec3((_x + x) * Chunk::SizeX, (_y + y) * Chunk::SizeY, (_z + z) * Chunk::SizeZ));
						MVP = renderContext->getProjectionMatrix() * renderContext->getViewMatrix() * MVP;
						glUniformMatrix4fv(glGetUniformLocation(renderContext->getShaderManager()->getShader("Chunk")->getProgram(), "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
						_chunks[x][y][z]->render(renderContext);
					}
				}
			}
		}
	}

}

int		ChunkManager::getX() {
	return _x;
}

int		ChunkManager::getY() {
	return _y;
}

int		ChunkManager::getZ() {
	return _z;
}

void	ChunkManager::setOrigin(int x, int y, int z) {
	int sx, ex, stepx, sy, ey, stepy, sz, ez, stepz;
	if (x >= _x) {
		sx = 0;
		ex = SizeX - 1;
		stepx = 1;
	}
	else {
		sx = SizeX - 1;
		ex = 0;
		stepx = -1;
	}

	if (y >= _y) {
		sy = 0;
		ey = SizeY - 1;
		stepy = 1;
	}
	else {
		sy = SizeY - 1;
		ey = 0;
		stepy = -1;
	}

	if (z >= _z) {
		sz = 0;
		ez = SizeZ - 1;
		stepz = 1;
	}
	else {
		sz = SizeZ - 1;
		ez = 0;
		stepz = -1;
	}

	for (int ix = sx; ix != ex; ix += stepx) {
		for (int iy = sy; iy != ey; iy += stepy) {
			for (int iz = sz; iz != ez; iz += stepz) {
				int xoffset = x - _x;
				int yoffset = y - _y;
				int zoffset = z - _z;
				if (ix + xoffset >= 0 and ix + xoffset < SizeX and iy + yoffset >= 0 and iy + yoffset < SizeY and iz + zoffset >= 0 and iz + zoffset < SizeZ)
					_chunks[ix][iy][iz] = _chunks[ix + xoffset][iy + yoffset][iz + zoffset];
				else
					_chunks[ix][iy][iz] = nullptr;
			}
		}
	}
	_x = x;
	_y = y;
	_z = z;
}

Chunk	*ChunkManager::getChunk(int x, int y, int z) {
	if (x < 0 or y < 0 or z < 0 or x >= SizeX or y >= SizeY or z >= SizeZ)
		throw std::exception();
	return _chunks[x][y][z];
}

void	ChunkManager::setChunk(Chunk *c, int x, int y, int z) {
	_chunks[x][y][z] = c;
}

void	ChunkManager::updateAsyncChunker() {
	for (int x = 0; x < SizeX; x++) {
		for (int y = 0; y < SizeY; y++) {
			for (int z = 0; z < SizeZ; z++) {
				if (_chunks[x][y][z] != nullptr) {
					if (not _chunks[x][y][z]->isSetup()) {
						_setupQueue.push(_chunks[x][y][z]);
					}
				}
			}
		}
	}
}

void ChunkManager::updateSetupQueue()
{
	int i = 0;
	while (_setupQueue.size() and i < CHUNKS_PER_FRAME)
	{
		Chunk *chunk = _setupQueue.front();
		if (chunk->isSetup() == false) {
			chunk->setup();
			i++;
		}
		_setupQueue.pop();
	}
}

void ChunkManager::updateRebuildQueue()
{
	int i = 0;
	while (_rebuildQueue.size() and i < CHUNKS_PER_FRAME)
	{
		Chunk *chunk = _rebuildQueue.front();
		chunk->generateMesh();
		i++;
		_rebuildQueue.pop();
	}
}

void	ChunkManager::updateUnloadQueue() {

}
