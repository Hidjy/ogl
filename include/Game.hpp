#pragma once

#include "IUserInterface.hpp"

#include "GUI.hpp"
#include "Player.hpp"
#include "Camera.hpp"
#include "World.hpp"

#include "IRenderContext.hpp"

class Game : public IUserInterface
{
private:
	GUI				*_gui;
	IRenderContext	*_renderContext;

	World	 	*_world;

	Player 		*_player;
	Camera 		*_camera;

public:
	Game();
	~Game();

	World	*getWorld();
	Player	*getPlayer();
	Camera	*getCamera();

	void	setRenderContext(IRenderContext *renderContext);

	void	initWorld();
	void	update(float dt);
	void	render();
};
