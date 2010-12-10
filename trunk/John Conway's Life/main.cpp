#include "Game.h"

int main(int argc, char** argv)
{
	if(!initSDL())			//initialize SDL
		return 1;

	Game Life;				//initialize game
	
	//main game loop
	while(!Life.toQuit)
	{
		Life.HandleInput();	//message loop
		Life.Draw();		//draw screen
		Life.Update();		//update game objects
	}

	SDL_Quit();				//quit SDL
	return 0;
}