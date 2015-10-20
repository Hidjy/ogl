#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "Block.hpp"
#include "ChunkRenderer.hpp"
#include "IRenderContext.hpp"

class ChunkRenderer;

class Chunk {
private:
	ChunkRenderer	*_chunkRenderer;

	bool		_setup;

	Block		****_blocks;

public:
	static const int LogSizeX = 5;
	static const int LogSizeY = 5;
	static const int LogSizeZ = 5;

	static const int SizeX = 1 << LogSizeX;
	static const int SizeY = 1 << LogSizeY;
	static const int SizeZ = 1 << LogSizeZ;

	static const int MaskX = SizeX - 1;
	static const int MaskY = SizeX - 1;
	static const int MaskZ = SizeX - 1;

public:
	Chunk();
	Chunk(Chunk const &src);
	~Chunk();

	bool	isSetup() const;

	Block	*getBlock(int x, int y, int z);

	void	setBlock(Block *b, int x, int y, int z);

	void	generateMesh();
	void	update(float dt);
	void	render(IRenderContext *renderContext);
	void	setup();
};
