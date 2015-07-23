#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Chunk.hpp"
#include "Shader.hpp"

#include "ChunkManager.hpp"

#include <vector>

class World {
public:
	ChunkManager	_chunkManager;
	//TODO: Must contain Player

public:
	World();
	~World();

	void	update(float dt);
	void	render(glm::vec3 pos, Shader shader);

	Chunk	&getChunk(int x, int y, int z);
	void	addChunk(Chunk *chunk);

	GLint	getWorldBlockId(float x, float y, float z);
	GLint	getWorldBlockId(glm::vec3 const &v);
};
