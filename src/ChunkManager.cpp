#include "ChunkManager.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Game.hpp"
#include "Chunk.hpp"
#include "ShaderManager.hpp"
#include "IRenderContext.hpp"

#include <exception>
#include <utility>

ChunkManager::ChunkManager() {
}

ChunkManager::~ChunkManager() {
}

void ChunkManager::update(float dt)
{
	updateAsyncChunker();

	updateLoadQueue();
	updateSetupQueue();
	updateRebuildQueue();

	updateUnloadQueue();

	updateVisibilityList();
	updateRenderList();

	// updateChunkList();
}

void	ChunkManager::render(IRenderContext *renderContext) {
	renderContext->getShaderManager()->getShader("Chunk")->use();

	for (auto it = _renderList.begin(); it != _renderList.end(); ++it) {
		glm::mat4 MVP;
		glm::vec3 pos = (*it)->getPos();
		MVP = glm::translate(MVP, glm::vec3(pos.x * Chunk::SizeX, pos.y * Chunk::SizeY, pos.z * Chunk::SizeZ));
		MVP = renderContext->getProjectionMatrix() * renderContext->getViewMatrix() * MVP;
		glUniformMatrix4fv(glGetUniformLocation(renderContext->getShaderManager()->getShader("Chunk")->getProgram(), "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
		(*it)->render(renderContext);
	}
}

void	ChunkManager::addChunk(Chunk *chunk) {
	_chunks.push_back(chunk);
	_loadQueue.push(chunk);
}

void	ChunkManager::setCamera(glm::vec3 cameraPosition, glm::vec3 cameraView)
{
	_cameraPos = cameraPosition;
	_cameraView = cameraView;
}

Chunk	&ChunkManager::getChunk(glm::vec3 pos) {
	for (auto it = _chunks.begin() ; it != _chunks.end(); ++it) {
		glm::vec3 cpos = (**it).getPos();
		if (pos == cpos)
			return (**it);
	}
	throw std::exception();
}

void	ChunkManager::updateAsyncChunker() {

}

void ChunkManager::updateLoadQueue()
{
	int i = 0;
	while (_loadQueue.size() and i < CHUNKS_PER_FRAME)
	{
		Chunk *chunk = _loadQueue.front();
		if (chunk->isLoaded() == false) {
			chunk->load();
			_setupQueue.push(chunk);
			i++;
		}
		_loadQueue.pop();
	}
}

void ChunkManager::updateSetupQueue()
{
	int i = 0;
	while (_setupQueue.size() and i < CHUNKS_PER_FRAME)
	{
		Chunk *chunk = _setupQueue.front();
		if (chunk->isLoaded() and chunk->isSetup() == false) {
			chunk->setup();
			i++;
		}
		_setupQueue.pop();
	}
}

void ChunkManager::updateRebuildQueue()
{
	int i = 0;
	while (_rebuildQueue.size() and i < CHUNKS_PER_FRAME)
	{
		Chunk *chunk = _rebuildQueue.front();
		if (chunk->needRebuild()) {
			chunk->generateMesh();
			i++;
		}
		_rebuildQueue.pop();
	}
}

void ChunkManager::updateUnloadQueue()
{
	int i = 0;
	while (_unloadQueue.size() and i < CHUNKS_PER_FRAME)
	{
		Chunk *chunk = _unloadQueue.front();
		if (chunk->isLoaded()) {
			chunk->unload();
			i++;
		}
		_unloadQueue.pop();
	}
}

void ChunkManager::updateVisibilityList()
{
	_visibilityList.clear();
	glm::vec3 pos = _cameraPos;
	for (auto it = _chunks.begin(); it != _chunks.end(); ++it) {
		if (*it != nullptr) {
			glm::vec3 temp = glm::vec3(pos.x / Chunk::SizeX + 0.5f, pos.y / Chunk::SizeY + 0.5f, pos.z / Chunk::SizeZ + 0.5f) - (*it)->getPos();
			GLfloat distSqr = glm::dot(temp, temp);
			if (sqrt(distSqr) < 10)
				_visibilityList.push_back(*it);
		}
	}
}

void ChunkManager::updateRenderList()
{
	_renderList.clear();

	for(auto it = _visibilityList.begin(); it != _visibilityList.end(); ++it)
	{
		Chunk* pChunk = (*it);

		if(pChunk != nullptr)
		{
			if(pChunk->isLoaded() && pChunk->isSetup())
			{
				//Frustum Culling
				_renderList.push_back(pChunk);
			}
		}
	}
}
