#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Chunk.hpp"
#include "ChunkRenderer.hpp"
#include "Shader.hpp"

#include <vector>


Chunk::Chunk() : _pos(glm::vec3(0, 0, 0)), _empty(false) //FIXME
{
	_blocks = new Block**[SIZE];
	for(int i = 0; i < SIZE; i++)
	{
		_blocks[i] = new Block*[SIZE];

		for(int j = 0; j < SIZE; j++)
		{
			_blocks[i][j] = new Block[SIZE];
		}
	}

	_chunkRenderer.setPos(glm::vec3(_pos.x * SIZE, _pos.y * SIZE, _pos.z * SIZE));
	// _chunkRenderer.generateMesh(_blocks);
}

Chunk::Chunk(Chunk const &src) : Chunk() {
	_pos = src.getPos();
	_empty = src.empty();
	for (size_t x = 0; x < SIZE; x++) {
		for (size_t y = 0; y < SIZE; y++) {
			for (size_t z = 0; z < SIZE; z++) {
				_blocks[x][y][z] = src.getBlock(x, y, z);
			}
		}
	}
}

Chunk::~Chunk()
{
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			delete [] _blocks[i][j];
		}

		delete [] _blocks[i];
	}
	delete [] _blocks;
}

bool	Chunk::empty() const {
	return _empty;
}

glm::vec3	Chunk::getPos() const {
	return _pos;
}

Block 	Chunk::getBlock(int x, int y, int z) const {
	return _blocks[x][y][z];
}

Block 	&Chunk::getBlock(int x, int y, int z) {
	return _blocks[x][y][z];
}

void	Chunk::setPos(glm::vec3 pos) {
	_pos = pos;
	_chunkRenderer.setPos(glm::vec3(_pos.x * SIZE, _pos.y * SIZE, _pos.z * SIZE));
}

void	Chunk::setBlock(int x, int y, int z, Block block) {
	_blocks[x][y][z] = block;
	_empty = false; //Not accurate, see Chunk.hpp
}


void	Chunk::generateMesh() {
	if (_empty == false)
		_chunkRenderer.generateMesh(_blocks);
}

void	Chunk::render(Shader shader) {
	if (_empty)
		return;
	_chunkRenderer.render(shader);
}

Chunk	&Chunk::operator=(Chunk const &src) {
	_pos = src.getPos();
	_empty = src.empty();

	for (size_t x = 0; x < SIZE; x++) {
		for (size_t y = 0; y < SIZE; y++) {
			for (size_t z = 0; z < SIZE; z++) {
				_blocks[x][y][z] = src.getBlock(x, y, z);
			}
		}
	}

	return *this;
}
