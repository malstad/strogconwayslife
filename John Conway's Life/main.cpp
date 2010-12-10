#include "Game.h"

int main(int argc, char** argv)
{
	if(!initSDL())
		return 1;

	Game Life;
	
	//main game loop
	while(!Life.toQuit)
	{
		Life.Draw();
		Life.HandleInput();
		Life.Update();
	}

	SDL_Quit();
	return 0;
}