#pragma once

#include "Mesh.hpp"
#include "Chunk.hpp"
#include "IRenderContext.hpp"

#define AO_COEFF 0.95f

class Chunk;

class ChunkRenderer {
private:
	Mesh _mesh;

public:
	ChunkRenderer();

	void	generateMesh(Chunk *chunk);
	void	render(IRenderContext *renderContext);
};
