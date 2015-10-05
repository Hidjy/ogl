#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "Chunk.hpp"
#include "Shader.hpp"
#include "Renderer.hpp"

#include <vector>
#include <queue>

#define CHUNKS_PER_FRAME 1 //TODO: Determine a good value

class ChunkManager {
private:
	glm::vec3				_cameraPos;
	glm::vec3				_cameraView;

	std::vector<Chunk *>	_chunks;

	std::queue<Chunk *>		_loadQueue;
	std::queue<Chunk *>		_setupQueue;
	std::queue<Chunk *>		_rebuildQueue;
	std::queue<Chunk *>		_unloadQueue;

	std::vector<Chunk *>	_visibilityList;
	std::vector<Chunk *>	_renderList;

	bool					_forceVisibilityUpdate;

public:
	ChunkManager();
	~ChunkManager();

	void	setCamera(glm::vec3 cameraPosition, glm::vec3 cameraView);
	void	addChunk(Chunk *chunk);

	Chunk	&getChunk(glm::vec3 pos);

	void 	update(float dt);
	void 	render(Renderer *renderer);

	void	updateAsyncChunker();

	void	updateLoadQueue();
	void	updateSetupQueue();
	void	updateRebuildQueue();
	void	updateUnloadQueue();

	void	updateVisibilityList();
	void	updateRenderList();

	// void	updateChunkList();

};
