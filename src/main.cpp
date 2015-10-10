#include "GUI.hpp"
#include "Game.hpp"

int main()
{
	GUI *gui = GUI::instance();
	Game game;

	while(gui->shouldClose() == false)
	{
		gui->doUpdate(game);
		gui->doRender(game);
	}

	return 0;
}
