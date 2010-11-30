#include "Grid.h"
#include "Button.h"

//globals
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
SDL_Event g_seEvent;					// receives event information
SDL_Surface* g_ssScreen = NULL;			// the main screen
SDL_Rect g_srPlayButton;				// play button that starts the simulation
SDL_Rect g_srStopButton;				// stop button that stops the simulation

void handleMouseEvents(Grid &PlayingGrid);
void Update(Grid &PlayingGrid, bool isPlaying);

int main(int argc, char** argv)
{
	SDL_Surface* ssSpriteSheet = NULL;	// surface that holds the sprite sheet for the cell
	SDL_Surface* ssButtons = NULL;		// surface that holds the sprite sheet for the buttons

	//attempts to initialize SDL, and quits if failed
	if(!init(g_ssScreen, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP))
		return 1;
	//attempts to load the sprite sheet and quit if that failed
	ssSpriteSheet = loadFile("sprites.png");
	ssButtons = loadFile("buttons.png");			
	if(NULL == ssSpriteSheet || NULL == ssButtons)
		return 1;

	bool toQuit = false;
	bool isPlaying = false;
	Grid PlayingGrid;
	Button PlayButton(PLAY_UNPRESSED, SCREEN_WIDTH, SCREEN_HEIGHT);
	Button StopButton(STOP_UNPRESSED, SCREEN_WIDTH, SCREEN_HEIGHT);
	
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
		PlayingGrid.Draw(ssSpriteSheet, g_ssScreen);
		PlayButton.Draw(ssButtons, g_ssScreen);
		StopButton.Draw(ssButtons, g_ssScreen);
		Update(PlayingGrid, isPlaying);
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

		if(PlayingGrid.isWithinBounds(CoordX, CoordY))
			PlayingGrid.LocateAndFlipCell(CoordX, CoordY);

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