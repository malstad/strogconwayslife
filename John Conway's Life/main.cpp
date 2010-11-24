#include "Grid.h"

//globals
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;

void handleMouseEvents();

int main(int argc, char** argv)
{
	SDL_Surface* ssScreen = NULL;		// the main screen
	SDL_Surface* ssSpriteSheet = NULL;	// surface that holds the sprite sheet for the cell
	SDL_Event seEvent;					// receives event information

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

	while(!toQuit)
	{
		while(SDL_PollEvent(&seEvent))
		{
			//handleMouseEvents();
			if(seEvent.type == SDL_QUIT)
			{
				toQuit = true;
			}
		}

		//Update();
		//if(isPlaying)
		//	Play();
	}

	SDL_FreeSurface(ssSpriteSheet);
	SDL_Quit();
	return 0;
}



void handleMouseEvents()
{
	//float PosX, PosY;

	////if the user left clicks
	//if(g_seEvent.type == SDL_MOUSEBUTTONDOWN && g_seEvent.button.button == SDL_BUTTON_LEFT)
	//{
	//	PosX = g_seEvent.button.x;
	//	PosY = g_seEvent.button.y;

	//	//make sure click was within the bounds of the grid
	//	if(PosX >

	//	PosX /= cellWidth;
	//	PosY /= cellHeight;

	//	//determine what cell was clicked

	//}
}