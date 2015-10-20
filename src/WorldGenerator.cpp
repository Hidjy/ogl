#include "WorldGenerator.hpp"

#include "Chunk.hpp"
#include "BlockTypeFactory.hpp"

WorldGenerator::WorldGenerator() {
	_blockTypeFactory = new BlockTypeFactory();
}

void	WorldGenerator::generateChunk(Chunk *chunk, int x, int y, int z) {
	for (int ix = 0; ix < Chunk::SizeX; ix++) {
		for (int iy = 0; iy < Chunk::SizeY; iy++) {
			for (int iz = 0; iz < Chunk::SizeZ; iz++) {
				Block *block = chunk->getBlock(ix, iy, iz);
				if (y * Chunk::SizeY + iy <= 0) {
					block->setActive(true);
					block->setType(_blockTypeFactory->create("Water"));
				}
				else if (y * Chunk::SizeY + iy == 1 and 0 == (rand() % 100)) {
					block->setActive(true);
					block->setType(_blockTypeFactory->create("Sand"));
				}
			}
		}
	}
}
