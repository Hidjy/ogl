#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "Block.hpp"
#include "ShaderManager.hpp"
#include "ChunkRenderer.hpp"
#include "IRenderContext.hpp"

//TODO: Block counter (for accurate _empty)

class ChunkRenderer;

class Chunk {
private:
	glm::vec3	_pos;

	ChunkRenderer	*_chunkRenderer;

	bool		_empty;
	bool		_loaded;
	bool		_setup;
	bool		_needRebuild;

	GLuint		_blockCount;

	Block		***_blocks;

public:
	static const int SIZE = 32;

public:
	Chunk();
	Chunk(Chunk const &src);
	~Chunk();

	bool		empty() const;
	bool		isLoaded() const;
	bool		isSetup() const;
	bool		needRebuild() const;

	GLuint	countBlocks();

	glm::vec3	const &getPos() const;
	Block		getBlock(int x, int y, int z) const;

	Block		&getBlock(int x, int y, int z);

	void		setPos(glm::vec3 pos);
	void		setBlock(int x, int y, int z, Block block);

	void	generateMesh();
	void	update(float dt);
	void	render(IRenderContext *renderContext);
	void	load();
	void	unload();
	void	setup();

	Chunk	&operator=(Chunk const &src);
};
