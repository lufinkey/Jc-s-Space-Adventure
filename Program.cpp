#include "Game.h"

int main(int argc, char *argv[])
{
	JcAdventure::Game*game = new JcAdventure::Game();
	game->Run(Application::ORIENTATION_LANDSCAPE, false);
	delete game;
	return 0;
}