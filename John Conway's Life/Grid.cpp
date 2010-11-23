#include "Grid.h"

Grid::Grid(): m_nBuffers(2), 
				m_nRows(50), 
				m_nColumns(63), 
				m_cellWidth(11), 
				m_cellHeight(10)
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

//SDL_Surface* Grid::CreateDrawGrid(SDL_Surface* SpriteSheet)
//{
//	for(int r = 0; r < nRows; r++)
//	{
//		for(int c = 0; c < nColumns; c++)
//		{
//			//determine what color to fill the current cell with
//			if(g_grids[0][r][c])
//				currentClip = alive;
//			else 
//				currentClip = dead;
//
//			//apply the current cell to the screen
//			applySurface(m_srDisplayOffset.x, m_srDisplayOffset.y, SpriteSheet, g_ssScreen, &currentClip);
//
//
//			//increment horizontal offset
//			offset.x += cellWidth;
//		}
//		offset.x = 50;			 // after drawing a horizontal line, reset horizontal offset
//		offset.y += cellHeight; // increment vertical offset
//	}
//}


//Grid::~Grid()
//{
//	for(int b = 0; b < m_nBuffers; b++)
//	{
//		for(int r = 0; r < m_nRows; r++)
//		{
//			delete [] m_grids[b][r];
//		}
//
//		delete [] m_grids[b];
//	}
//
//	delete [] m_grids;
//}