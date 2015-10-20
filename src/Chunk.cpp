#define GLEW_STATIC
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <vector>

#include "Chunk.hpp"
#include "ChunkRenderer.hpp"
#include "ShaderManager.hpp"
#include "Color.hpp"
#include "IRenderContext.hpp"

Chunk::Chunk() : _setup(false)
{
	_blocks = new Block***[SizeX];
	for (int i = 0; i < SizeX; i++)
	{
		_blocks[i] = new Block**[SizeY];

		for (int j = 0; j < SizeY; j++)
		{
			_blocks[i][j] = new Block*[SizeZ];
			for (int k = 0; k < SizeZ; k++)
				_blocks[i][j][k] = nullptr;
		}
	}

	_chunkRenderer = new ChunkRenderer();
}

Chunk::~Chunk()
{
	for (int i = 0; i < SizeX; ++i)
	{
		for (int j = 0; j < SizeY; ++j)
		{
			for (int k = 0; k < SizeZ; k++)
			{
				if (_blocks[i][j][k] != nullptr)
					delete _blocks[i][j][k];
			}
			delete [] _blocks[i][j];
		}
		delete [] _blocks[i];
	}
	delete [] _blocks;

	delete _chunkRenderer;
}

bool		Chunk::isSetup() const {
	return _setup;
}

Block 	*Chunk::getBlock(int x, int y, int z) {
	if (x < 0 or y < 0 or z < 0 or x >= SizeX or y >= SizeY or z >= SizeZ)
		throw std::exception();
	if (_blocks[x][y][z] == nullptr)
		_blocks[x][y][z] = new Block();
	return _blocks[x][y][z];
}

void	Chunk::setBlock(Block *b, int x, int y, int z) {
	_blocks[x][y][z] = b;
}

void	Chunk::generateMesh() {
	_chunkRenderer->generateMesh(this);
}

void	Chunk::render(IRenderContext *renderContext) {
	if (_setup)
		_chunkRenderer->render(renderContext);
}

void	Chunk::setup() {
	generateMesh();
	_setup = true;
}
