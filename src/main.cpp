#include "Game.hpp"

int main()
{
	Game::init();

	while(!Game::shouldClose())
	{
		Game::update();
		Game::draw();
	}

	Game::deinit();
	return 0;
}
