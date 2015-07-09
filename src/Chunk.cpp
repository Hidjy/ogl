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

Chunk::Chunk(glm::vec3 pos) : _pos(pos), _empty(true), _sectionsLoaded(false), _sectionsGenerated(false) {
	for (size_t x = 0; x < CHUNK_SIZE; x++) {
		for (size_t y = 0; y < CHUNK_SIZE; y++) {
			for (size_t z = 0; z < CHUNK_SIZE; z++) {
				this->_blocks[x][y][z] = 0;
			}
		}
	}
}

Chunk::~Chunk() {
	if (this->_sectionsLoaded == false)
		return;
	delete [] this->_sections;
}

void	Chunk::fill(int (*data)[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE]) {
	this->_empty = false;
	for (size_t x = 0; x < CHUNK_SIZE; x++) {
		for (size_t y = 0; y < CHUNK_SIZE; y++) {
			for (size_t z = 0; z < CHUNK_SIZE; z++) {
				this->_blocks[x][y][z] = (*data)[x][y][z];
			}
		}
	}
}

void	Chunk::loadSections() {
	if (this->_sectionsLoaded == true)
		return;
	this->_sections = new Section[CHUNK_RATIO * CHUNK_RATIO * CHUNK_RATIO];
	for (size_t x = 0; x < CHUNK_RATIO; x++) {
		for (size_t y = 0; y < CHUNK_RATIO; y++) {
			for (size_t z = 0; z < CHUNK_RATIO; z++) {
				this->_sections[x + y * CHUNK_RATIO + z * CHUNK_RATIO * CHUNK_RATIO].setPos(glm::vec3(this->_pos.x * CHUNK_SIZE + x * SECTION_SIZE, this->_pos.y * CHUNK_SIZE + y * SECTION_SIZE, this->_pos.z * CHUNK_SIZE + z * SECTION_SIZE));
			}
		}
	}
}

void	Chunk::getSectionData(int (*data)[SECTION_SIZE][SECTION_SIZE][SECTION_SIZE], int x, int y, int z) {
	for (size_t destX = 0; destX < SECTION_SIZE; destX++) {
		for (size_t destY = 0; destY < SECTION_SIZE; destY++) {
			for (size_t destZ = 0; destZ < SECTION_SIZE; destZ++) {
				(*data)[destX][destY][destZ] = this->_blocks[x * SECTION_SIZE + destX][y * SECTION_SIZE + destY][z * SECTION_SIZE + destZ];
			}
		}
	}
}

void	Chunk::generateSections() {
	if (this->_empty)
		return;
	if (this->_sectionsLoaded == false)
		this->loadSections();
	for (size_t x = 0; x < CHUNK_RATIO; x++) {
		for (size_t y = 0; y < CHUNK_RATIO; y++) {
			for (size_t z = 0; z < CHUNK_RATIO; z++) {
				int cubes[SECTION_SIZE][SECTION_SIZE][SECTION_SIZE];
				this->getSectionData(&cubes, x, y, z); //fill the cubes buffer
				this->_sections[x + y * CHUNK_RATIO + z * CHUNK_RATIO * CHUNK_RATIO].generateMesh(cubes);
			}
		}
	}
	this->_sectionsGenerated = true;
}

void	Chunk::render(Shader shader) {
	if (this->_empty)
		return;
	if (this->_sectionsGenerated == false)
		return;
	for (size_t x = 0; x < CHUNK_RATIO; x++) {
		for (size_t y = 0; y < CHUNK_RATIO; y++) {
			for (size_t z = 0; z < CHUNK_RATIO; z++) {
				this->_sections[x + y * CHUNK_RATIO + z * CHUNK_RATIO * CHUNK_RATIO].render(shader);
			}
		}
	}
}
