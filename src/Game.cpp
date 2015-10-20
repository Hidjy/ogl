#include "Game.hpp"

#include "Player.hpp"
#include "Camera.hpp"
#include "World.hpp"

#include "IRenderContext.hpp"
#include "RenderContext.hpp"

Game::Game() {
	_gui = GUI::instance();

	_world = new World();
	_player = new Player();
	_camera = new Camera();

	_world->setPlayer(_player);

	_player->setWorld(_world);
	_player->setCamera(_camera);

	_renderContext = new RenderContext();
	_renderContext->setProjectionMatrix(glm::perspective(45.0f, _gui->getAspectRatio(), 0.01f, 10000.0f));
	_renderContext->setViewMatrix(_camera->getViewMatrix());

	Shader *blockShader = new Shader();
	blockShader->loadFromFile(GL_VERTEX_SHADER,"shaders/chunk.vs");
	blockShader->loadFromFile(GL_FRAGMENT_SHADER,"shaders/chunk.fs");
	blockShader->createAndLinkProgram();
	_renderContext->getShaderManager()->setShader("Chunk", blockShader);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

Game::~Game() {
	delete _world;
	delete _player;
	delete _camera;
	delete _renderContext;
}

World	*Game::getWorld() {
	return _world;
}

Player	*Game::getPlayer() {
	return _player;
}

Camera	*Game::getCamera() {
	return _camera;
}

void	Game::setRenderContext(IRenderContext *renderContext) {
	_renderContext = renderContext;
}

void	Game::initWorld() {
	//Generate world
}

void	Game::update(float dt) {
	_world->update(dt);
	_player->update(dt);
}

void	Game::render() {
	_renderContext->setViewMatrix(_camera->getViewMatrix());

	_renderContext->getShaderManager()->getShader("Chunk")->use();
	_world->render(_renderContext);
	_renderContext->getShaderManager()->getShader("Chunk")->unUse();
}
