#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Chunk.hpp"
#include "Shader.hpp"

#include <vector>

class World {
public:
	std::vector<glm::vec3>	_chunkPos;
	std::vector<Chunk>		_chunks;

public:
	World();
	~World();

	Chunk	&getChuck(int x, int y, int z);
	void	add(Chunk const &chunk);
	void	renderNear(glm::vec3 pos, Shader shader);
};
