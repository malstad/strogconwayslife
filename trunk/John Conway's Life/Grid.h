#ifndef GRID_H
#define GRID_H

#include "MySDLFunctions.h"
#include <Windows.h>

class Grid
{
protected:
	int m_nBuffers;						// number of buffers the grid will use
	int m_iDrawBuffer;					// variable holding the value of what buffer will be drawn to screen
	int m_iLogicBuffer;					// variable holding the value of what buffer the logic will be written to
	int m_nRows;						// number of rows the grid will have
	int m_nColumns;						// number of coulumns the grid will have
	int m_cellWidth;					// width of a cell in the grid
	int m_cellHeight;					// height of a cell in the grid
	
	bool*** m_grids;					// three dimensional array that stores bools
	SDL_Rect m_srDisplayGrid;			// rect that will hold the display
	SDL_Surface* m_ssCellSprites;		// surface holding the sprite sheet of a single cell
	SDL_Rect m_srDisplayOffset;			// how much the grid will be offset
	SDL_Rect m_srCellSpecs;				// dimensions of a single cell

	//functions only used by Grid class
	int findCellNeighbors(int xPos, int yPos);	// determines the number of neighbors a given cell has on the grid

public:
	Grid();
	bool Initializer();
	void Draw(SDL_Surface* Screen);
	bool HandleMouseInput(float x, float y);
	void Update();
	bool CheckCell(int sourceBuffer, int r, int c);
	//get functions
	SDL_Rect getCellSpecs() { return m_srCellSpecs; }
	SDL_Rect getMainRectOffset() { return m_srDisplayOffset; }
	SDL_Rect getMainRect() { return m_srDisplayGrid; }
	~Grid();							//destructor
};

#endif