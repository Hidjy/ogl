#pragma once

#include "Chunk.hpp"
#include "BlockTypeFactory.hpp"

class WorldGenerator {
private:
	BlockTypeFactory	*_blockTypeFactory;

public:
	WorldGenerator();

	void	generateChunk(Chunk *chunk, int x, int y, int z);
};
