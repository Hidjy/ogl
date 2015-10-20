#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "Chunk.hpp"
#include "Shader.hpp"
#include "ShaderManager.hpp"
#include "IRenderContext.hpp"

#include <vector>
#include <queue>

#define CHUNKS_PER_FRAME 1 //TODO: Determine a good value

class ChunkManager {
private:
	Chunk					****_chunks;

	int						_x;
	int						_y;
	int						_z;

	std::queue<Chunk *>		_setupQueue;
	std::queue<Chunk *>		_rebuildQueue;
	std::queue<Chunk *>		_unloadQueue;

public:
	static const int SizeX = 12;
	static const int SizeY = 3;
	static const int SizeZ = 12;

public:
	ChunkManager();
	~ChunkManager();

	void	setOrigin(int x, int y, int z);

	int		getX();
	int		getY();
	int		getZ();

	Chunk	*getChunk(int x, int y, int z);

	void	setChunk(Chunk *c, int x, int y, int z);

	void 	update(float dt);
	void 	render(IRenderContext *renderContext);

	void	updateAsyncChunker();

	void	updateSetupQueue();
	void	updateRebuildQueue();
	void	updateUnloadQueue();

	// void	updateChunkList();

};
