#include "Game.h"

//globals
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
SDL_Event g_seEvent;					// receives event information
SDL_Surface* g_ssScreen = NULL;			// the main screen

void handleMouseEvents(Grid &PlayingGrid);
void Update(Grid &PlayingGrid, bool isPlaying);

int main(int argc, char** argv)
{

	//attempts to initialize SDL, and quits if failed
	/*if(!init(g_ssScreen, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP))
		return 1;*/

	if(!initSDL())
	{
		return 1;
	}

	//bool toQuit = false;
	Game Life;
	//bool isPlaying = false;
	//Grid PlayingGrid;
	//Button PlayButton(PLAY_UNPRESSED, SCREEN_WIDTH, SCREEN_HEIGHT);
	//Button StopButton(STOP_UNPRESSED, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	//main game loop
	while(!Life.toQuit)
	{
		Life.Draw();
		Life.HandleInput();
		Life.Update();
		//PlayingGrid.Draw(g_ssScreen);
		//PlayButton.Draw(g_ssScreen);
		//StopButton.Draw(g_ssScreen);
		//Update(PlayingGrid, isPlaying);
	}

	SDL_Quit();
	return 0;
}



void handleMouseEvents(Grid &PlayingGrid)
{
	//if the user left clicks
	if(g_seEvent.type == SDL_MOUSEBUTTONDOWN && g_seEvent.button.button == SDL_BUTTON_LEFT)
	{
		float CoordX, CoordY;
		
		CoordX = g_seEvent.button.x;
		CoordY = g_seEvent.button.y;

		PlayingGrid.HandleMouseInput(CoordX, CoordY);

	}
}

void Update(Grid &PlayingGrid, bool isPlaying)
{
	if(isPlaying)
	{
		//PlayingGrid.PlayLife();
	}

	SDL_Flip(g_ssScreen);
}