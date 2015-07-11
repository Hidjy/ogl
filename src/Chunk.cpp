#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Chunk.hpp"
#include "Section.hpp"
#include "Shader.hpp"
#include "Cube.hpp"

#include <vector>

Chunk::Chunk() : Chunk(glm::vec3(0,0,0)) {

}

Chunk::Chunk(glm::vec3 pos) : _pos(pos), _empty(true), _sectionsLoaded(false), _sectionsGenerated(false) {
	for (size_t x = 0; x < CHUNK_SIZE; x++) {
		for (size_t y = 0; y < CHUNK_SIZE; y++) {
			for (size_t z = 0; z < CHUNK_SIZE; z++) {
				_blocks[x][y][z] = 0;
			}
		}
	}
}

Chunk::Chunk(Chunk const &src) : _pos(src.getPos()), _empty(src._empty), _sectionsLoaded(false), _sectionsGenerated(false) {
	for (size_t x = 0; x < CHUNK_SIZE; x++) {
		for (size_t y = 0; y < CHUNK_SIZE; y++) {
			for (size_t z = 0; z < CHUNK_SIZE; z++) {
				_blocks[x][y][z] = src._blocks[x][y][z];
			}
		}
	}
}

Chunk::~Chunk() {
	if (_sectionsLoaded == false)
		return;
	delete [] _sections;
}

bool	Chunk::empty() const {
	return _empty;
}

glm::vec3	Chunk::getPos() const {
	return _pos;
}

int	Chunk::getBlock(int x, int y, int z) const {
	return _blocks[x][y][z];
}

void	Chunk::fill(int (*data)[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE]) {
	_empty = false;
	for (size_t x = 0; x < CHUNK_SIZE; x++) {
		for (size_t y = 0; y < CHUNK_SIZE; y++) {
			for (size_t z = 0; z < CHUNK_SIZE; z++) {
				_blocks[x][y][z] = (*data)[x][y][z];
			}
		}
	}
}

void	Chunk::loadSections() {
	if (_sectionsLoaded == true)
		return;
	_sections = new Section[CHUNK_RATIO * CHUNK_RATIO * CHUNK_RATIO];
	for (size_t x = 0; x < CHUNK_RATIO; x++) {
		for (size_t y = 0; y < CHUNK_RATIO; y++) {
			for (size_t z = 0; z < CHUNK_RATIO; z++) {
				_sections[x + y * CHUNK_RATIO + z * CHUNK_RATIO * CHUNK_RATIO].setPos(glm::vec3(_pos.x * CHUNK_SIZE + x * SECTION_SIZE, _pos.y * CHUNK_SIZE + y * SECTION_SIZE, _pos.z * CHUNK_SIZE + z * SECTION_SIZE));
			}
		}
	}
}

void	Chunk::getSectionData(int (*data)[SECTION_SIZE][SECTION_SIZE][SECTION_SIZE], int x, int y, int z) {
	for (size_t destX = 0; destX < SECTION_SIZE; destX++) {
		for (size_t destY = 0; destY < SECTION_SIZE; destY++) {
			for (size_t destZ = 0; destZ < SECTION_SIZE; destZ++) {
				(*data)[destX][destY][destZ] = _blocks[x * SECTION_SIZE + destX][y * SECTION_SIZE + destY][z * SECTION_SIZE + destZ];
			}
		}
	}
}

void	Chunk::generateSections() {
	if (_empty)
		return;
	if (_sectionsLoaded == false)
		loadSections();
	for (size_t x = 0; x < CHUNK_RATIO; x++) {
		for (size_t y = 0; y < CHUNK_RATIO; y++) {
			for (size_t z = 0; z < CHUNK_RATIO; z++) {
				int cubes[SECTION_SIZE][SECTION_SIZE][SECTION_SIZE];
				getSectionData(&cubes, x, y, z); //fill the cubes buffer
				_sections[x + y * CHUNK_RATIO + z * CHUNK_RATIO * CHUNK_RATIO].generateMesh(cubes);
			}
		}
	}
	_sectionsGenerated = true;
}

void	Chunk::render(Shader shader) {
	if (_empty)
		return;
	if (_sectionsGenerated == false)
		generateSections();
	for (size_t x = 0; x < CHUNK_RATIO; x++) {
		for (size_t y = 0; y < CHUNK_RATIO; y++) {
			for (size_t z = 0; z < CHUNK_RATIO; z++) {
				_sections[x + y * CHUNK_RATIO + z * CHUNK_RATIO * CHUNK_RATIO].render(shader);
			}
		}
	}
}

Chunk	&Chunk::operator=(Chunk const &src) {
	_pos = src.getPos();
	_empty = src.empty();
	_sectionsLoaded = false;
	_sectionsGenerated = false;

	for (size_t x = 0; x < CHUNK_SIZE; x++) {
		for (size_t y = 0; y < CHUNK_SIZE; y++) {
			for (size_t z = 0; z < CHUNK_SIZE; z++) {
				_blocks[x][y][z] = src.getBlock(x, y, z);
			}
		}
	}
	return *this;
}
