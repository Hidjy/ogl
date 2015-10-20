#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "Chunk.hpp"
#include "ShaderManager.hpp"
#include "IRenderContext.hpp"
#include "ChunkManager.hpp"

#include "WorldGenerator.hpp"

#include <vector>

#include "Player.hpp"

class Player;

class World {
public:
	ChunkManager	_chunkManager;
	WorldGenerator	*_worldGenerator;
	Player			*_player;

public:
	static const int ViewX = 5;
	static const int ViewY = 1;
	static const int ViewZ = 5;

public:
	World();
	~World();

	void	update(float dt);
	void	render(IRenderContext *renderContext);

	Chunk	*getChunk(int x, int y, int z);
	Block	*getBlock(int x, int y, int z);

	void	setPlayer(Player *p);
};
