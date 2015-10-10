#include "Game.hpp"

#include "Player.hpp"
#include "Camera.hpp"
#include "World.hpp"
#include "Skybox.hpp"

#include "RenderContext.hpp"

Game::Game() {
	_skybox = new Skybox();
	_world = new World();
	_player = new Player();
	_camera = new Camera();

	_player->setWorld(_world);
	_player->setCamera(_camera);

	_renderContext = new RenderContext();
	_renderContext->setProjectionMatrix(glm::perspective(45.0f, 16.0f/9.0f, 0.01f, 10000.0f));//FIXME: Aspect Ratio getter from GUI or renderContext
	_renderContext->setViewMatrix(_camera->getViewMatrix());

	Shader *blockShader = new Shader();
	blockShader->loadFromFile(GL_VERTEX_SHADER,"shaders/block.vs");
	blockShader->loadFromFile(GL_FRAGMENT_SHADER,"shaders/block.fs");
	blockShader->createAndLinkProgram();
	_renderContext->getShaderManager()->setShader("Block", blockShader);

	Shader *skyboxShader = new Shader();
	skyboxShader->loadFromFile(GL_VERTEX_SHADER,"shaders/skybox.vs");
	skyboxShader->loadFromFile(GL_FRAGMENT_SHADER,"shaders/skybox.fs");
	skyboxShader->createAndLinkProgram();
	_renderContext->getShaderManager()->setShader("Skybox", skyboxShader);

}

Game::~Game() {
	delete _skybox;
	delete _world;
	delete _player;
	delete _camera;
	delete _renderContext;
}

World	*Game::getWorld() {
	return _world;
}

Skybox	*Game::getSkybox() {
	return _skybox;
}

Player	*Game::getPlayer() {
	return _player;
}

Camera	*Game::getCamera() {
	return _camera;
}

void	Game::setRenderContext(RenderContext *renderContext) {
	_renderContext = renderContext;
}

void	Game::initWorld() {
	//Generate world
}

void	Game::update(float dt) {
	_player->update(dt);
	_world->update(dt);
}

void	Game::render() {
	_renderContext->setViewMatrix(_camera->getViewMatrix());

	_renderContext->getShaderManager()->getShader("Skybox")->use();
	_skybox->render(_renderContext);
	_renderContext->getShaderManager()->getShader("Skybox")->unUse();

	_renderContext->getShaderManager()->getShader("Block")->use();
	_world->render(_renderContext);
	_renderContext->getShaderManager()->getShader("Block")->unUse();
}
