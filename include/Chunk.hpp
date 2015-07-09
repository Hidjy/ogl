#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Section.hpp"
#include "Shader.hpp"
#include "Cube.hpp"

#include <vector>

#define CHUNK_SIZE 32
#define CHUNK_RATIO (CHUNK_SIZE / SECTION_SIZE)

class Chunk {
private:
	glm::vec3	_pos;
	Section		*_sections;
	bool		_empty;
	bool		_sectionsLoaded;
	bool		_sectionsGenerated;

	int			_blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];

public:
	Chunk(glm::vec3 pos);
	~Chunk();

	void	fill(int (*data)[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE]);
	void	loadSections();
	void	getSectionData(int (*data)[SECTION_SIZE][SECTION_SIZE][SECTION_SIZE], int x, int y, int z);
	void	generateSections();
	void	render(Shader shader);
};
