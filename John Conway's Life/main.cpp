#include <stdlib.h>
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

//globals
bool*** g_grids;						// will be used as two, two-dimensional array of bools
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
const int cellHeight = 10;				// height of each cell on the grid
const int cellWidth = 11;				// wid                    th of each cell on the gridd
const int nBuffers = 2;					// number of buffers
int nRows = 50;							// number of rows
int nColumns = 63;						// number of columns
SDL_Rect g_srGrid;						// display grid
SDL_Surface* g_ssScreen = NULL;			// screen used for displaying
SDL_Surface* g_ssSpriteSheet = NULL;	// surface holding the sprite sheet
SDL_Event g_seEvent;					// event handler

void SetupGrid();
void DrawGrid();

//SDL related functions
bool init();
SDL_Surface* loadImage(std::string, SDL_Color);
bool loadFiles();
void applySurface(int, int, SDL_Surface*, SDL_Surface*, SDL_Rect*);
void handleMouseEvents();
void cleanup();

int main(int argc, char** argv)
{
	if(!init())
		return 1;
	if(!loadFiles())
		return 1;

	bool toQuit = false;
	bool isPlaying = false;

	SetupGrid();
	DrawGrid();

	SDL_Flip(g_ssScreen);

	while(!toQuit)
	{
		while(SDL_PollEvent(&g_seEvent))
		{
			//handleMouseEvents();
			if(g_seEvent.type == SDL_QUIT)
			{
				toQuit = true;
			}
		}

		//Update();
		//if(isPlaying)
		//	Play();
	}

	cleanup();
	return 0;
}

void SetupGrid()
{
	//allocate the array
	g_grids = new bool**[nBuffers];	//creates an array of length nBuffers of pointers to pointers to bools
	for(int b = 0; b < nBuffers; b++)
	{
		g_grids[b] = new bool*[nRows];	//creates an array of length nRows of pointers to bools
		for(int r = 0; r < nRows; r++)
		{
			g_grids[b][r] = new bool[nColumns];	//creates an array of length nColumns of bools
		}
	}

	for(int b = 0; b < nBuffers; b++)
	{
		for(int r = 0; r < nRows; r++)
		{
			for(int c = 0; c < nColumns; c++)
			{
				g_grids[b][r][c] = false;		//initialize all bools on both grids to be false
			}
		}
	}

	// setup the visible grid
	g_srGrid.x = 0;
	g_srGrid.y = 0;
	g_srGrid.w = SCREEN_WIDTH;
	g_srGrid.h = SCREEN_HEIGHT;

}

void DrawGrid()
{
	SDL_Rect offset, dead, alive, currentClip;
	offset.x = 50;
	offset.y = 20;
	dead.x = 0;
	dead.y = 0;
	dead.w = cellWidth;
	dead.h = cellHeight;

	alive.x = 12;
	alive.y = 0;
	alive.w = cellWidth;
	alive.h = cellHeight;

}

bool init()
{
	//initialize all subsytems
	if(-1 == SDL_Init(SDL_INIT_EVERYTHING))
		return false;

	//initialize screen
	g_ssScreen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(NULL == g_ssScreen)	//if there was an error, return false
		return false;

	SDL_WM_SetCaption("John Conway's Game of Life", NULL);

	return true;
}

SDL_Surface* loadImage(std::string sFileName, SDL_Color* key)
{
	SDL_Surface* loadedImage;
	SDL_Surface* optimizedImage;

	loadedImage = IMG_Load(sFileName.c_str());

	if(NULL != loadedImage)
	{
		optimizedImage = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);

		//sets color key as long as optimizing the image didn't fail and user didn't pass a NULL value for key
		if(NULL != optimizedImage && NULL != key)
		{
			Uint32 colorkey = SDL_MapRGB(optimizedImage->format, key->r, key->g, key->b);
			SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
		}
	}

	return optimizedImage;
}

bool loadFiles()		// uses loadImage
{
	g_ssSpriteSheet = loadImage("sprites.png", NULL);	//load sprites

	//check if process failed
	if(NULL == g_ssSpriteSheet)
	{
		return false;
	}

	return true;
}


void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, clip, destination, &offset);
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

void cleanup()
{

	SDL_FreeSurface(g_ssSpriteSheet);
	SDL_Quit();							// quit SDL

}