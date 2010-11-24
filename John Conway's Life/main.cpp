#include "Grid.h"

//globals
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
SDL_Event g_seEvent;					// receives event information

void handleMouseEvents(Grid &PlayingGrid);

int main(int argc, char** argv)
{
	SDL_Surface* ssScreen = NULL;		// the main screen
	SDL_Surface* ssSpriteSheet = NULL;	// surface that holds the sprite sheet for the cell

	if(!init(ssScreen, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP))
		return 1;
	ssSpriteSheet = loadFile("sprites.png");
	if(NULL == ssSpriteSheet)
		return 1;

	bool toQuit = false;
	bool isPlaying = false;
	Grid PlayingGrid;
	
	//grid takes the sprite sheet and applies the grid to the screen
	PlayingGrid.CreateDrawGrid(ssSpriteSheet, ssScreen);

	SDL_Flip(ssScreen);

	//main game loop
	while(!toQuit)
	{
		//message loop
		while(SDL_PollEvent(&g_seEvent))
		{
			handleMouseEvents(PlayingGrid);
			if(g_seEvent.type == SDL_QUIT)
			{
				toQuit = true;
			}
		}
		PlayingGrid.CreateDrawGrid(ssSpriteSheet, ssScreen);
		SDL_Flip(ssScreen);

		//Update();
		//Draw();
	}

	SDL_FreeSurface(ssSpriteSheet);
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

		PlayingGrid.LocateAndFlipCell(CoordX, CoordY);

	}
}