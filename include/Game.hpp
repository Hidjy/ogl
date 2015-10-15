#pragma once

#include "IUserInterface.hpp"

#include "GUI.hpp"
#include "Player.hpp"
#include "Camera.hpp"
#include "World.hpp"
#include "Skybox.hpp"

#include "IRenderContext.hpp"

class Game : public IUserInterface
{
private:
	GUI				*_gui;
	IRenderContext	*_renderContext;

	World	 	*_world;
	Skybox 		*_skybox;//TODO: Sky Class ?
	Player 		*_player;
	Camera 		*_camera;

public:
	Game();
	~Game();

	World	*getWorld();
	Skybox	*getSkybox();
	Player	*getPlayer();
	Camera	*getCamera();

	void	setRenderContext(IRenderContext *renderContext);

	void	initWorld();
	void	update(float dt);
	void	render();
};
