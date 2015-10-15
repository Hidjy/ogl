#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "Chunk.hpp"
#include "ShaderManager.hpp"
#include "IRenderContext.hpp"
#include "ChunkManager.hpp"

#include "BlockTypeFactory.hpp"

#include <vector>

class World {
public:
	ChunkManager	_chunkManager;
	BlockTypeFactory *_blockTypeFactory;
	//TODO: Must contain Player

public:
	World();
	~World();

	void	update(float dt);
	void	render(IRenderContext *renderContext);

	Chunk	&getChunk(int x, int y, int z);
	void	addChunk(Chunk *chunk);

	GLint	getWorldBlockId(float x, float y, float z);
	GLint	getWorldBlockId(glm::vec3 const &v);
};
