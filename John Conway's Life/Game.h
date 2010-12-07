#ifndef GAME_H
#define GAME_H

#include "Grid.h"
#include "Button.h"

class Game
{
private:
	SDL_Event m_seEvent;					// receives event information
	SDL_Surface* m_ssScreen;				// the main screen
	Grid m_gCellGrid;						// the grid of cells
	Button m_bPlay;							// play button
	Button m_bStop;							// stop button
	bool m_isPlaying;						// flag used to have the game simulate
	const int SCREEN_WIDTH;					// width of the screen
	const int SCREEN_HEIGHT;				// height of the screen
	const int SCREEN_BPP;					// bits per pixel

public:
	bool toQuit;							// flag used to stop the program
	Game();									// main constructor
	void Draw();							// draws everything onto the screen
	void HandleInput();						// handles user input and modifies objects within the game
	void Update();

};

#endif