#include "Grid.h"

Grid::Grid(): m_nBuffers(2), 
				m_nRows(50), 
				m_nColumns(63), 
				m_cellWidth(11), 
				m_cellHeight(10),
				m_ssDisplaySurface(NULL)
{
	//allocate the array
	m_grids = new bool**[m_nBuffers];	//creates an array of length m_nBuffers of pointers to pointers to bools
	for(int b = 0; b < m_nBuffers; b++)
	{
		m_grids[b] = new bool*[m_nRows];	//creates an array of length m_nRows of pointers to bools
		for(int r = 0; r < m_nRows; r++)
		{
			m_grids[b][r] = new bool[m_nColumns];	//creates an array of length m_nColumns of bools
		}
	}

	for(int b = 0; b < m_nBuffers; b++)
	{
		for(int r = 0; r < m_nRows; r++)
		{
			for(int c = 0; c < m_nColumns; c++)
			{
				m_grids[b][r][c] = false;		//initialize all bools on both grids to be false
			}
		}
	}

	//setup the offset for the display grid
	m_srDisplayOffset.x = 50;
	m_srDisplayOffset.y = 20;

	// setup the visible grid
	m_srDisplayGrid.x = m_srDisplayOffset.x;
	m_srDisplayGrid.y = m_srDisplayOffset.y;
	m_srDisplayGrid.w = 700;
	m_srDisplayGrid.h = 500;
}

SDL_Surface* Grid::CreateDrawGrid(SDL_Surface* SpriteSheet, SDL_Surface* &Screen)
{
	SDL_Rect dead, alive, currentClip;
	
	dead.x = 0;
	dead.y = 0;
	dead.w = m_cellWidth;
	dead.h = m_cellHeight;

	alive.x = 12;
	alive.y = 0;
	alive.w = m_cellWidth;
	alive.h = m_cellHeight;

	for(int r = 0; r < m_nRows; r++)
	{
		for(int c = 0; c < m_nColumns; c++)
		{
			//determine what color to fill the current cell with
			if(m_grids[0][r][c])
				currentClip = alive;
			else 
				currentClip = dead;

			//apply the current cell to the screen
			applySurface(m_srDisplayOffset.x, m_srDisplayOffset.y, SpriteSheet, Screen, &currentClip);

			m_srDisplayOffset.x += m_cellWidth;	//increment horizontal offset
		}
		m_srDisplayOffset.x = 50;				// after drawing a horizontal line, reset horizontal offset
		m_srDisplayOffset.y += m_cellHeight;	// increment vertical offset
	}

	m_srDisplayOffset.y = 20;					// after drawing all vertical lines, reset vertical offset

	return m_ssDisplaySurface;
}


Grid::~Grid()
{
	for(int b = 0; b < m_nBuffers; b++)
	{
		for(int r = 0; r < m_nRows; r++)
		{
			delete [] m_grids[b][r];
		}

		delete [] m_grids[b];
	}

	delete [] m_grids;
}