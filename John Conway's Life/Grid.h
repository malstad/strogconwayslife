#ifndef GRID_H
#define GRID_H

#include "MySDLFunctions.h"

class Grid
{
protected:
	int m_nBuffers;						// number of buffers the grid will use
	int m_nRows;						// number of rows the grid will have
	int m_nColumns;						// number of coulumns the grid will have
	int m_cellWidth;					// width of a cell in the grid
	int m_cellHeight;					// height of a cell in the grid
	
	bool*** m_grids;					// three dimensional array that stores bools
	SDL_Rect m_srDisplayGrid;			// rect that will hold the display
	SDL_Surface* m_ssDisplaySurface;	// display picture
	SDL_Surface* m_ssCellSprites;		// surface holding the sprite sheet of a cell
	SDL_Rect m_srDisplayOffset;			// how much the display rect will be offset
	SDL_Rect m_srCellSpecs;				// dimensions of a single cell

public:
	Grid();
	void Draw(SDL_Surface* Screen);
	void LocateAndFlipCell(float x, float y);
	bool isWithinBounds(float x, float y);
	//get functions
	SDL_Rect getCellSpecs() { return m_srCellSpecs; }
	SDL_Rect getMainRectOffset() { return m_srDisplayOffset; }
	SDL_Rect getMainRect() { return m_srDisplayGrid; }
	~Grid();							//destructor
};

#endif