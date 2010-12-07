#include "Grid.h"

Grid::Grid(): m_nBuffers(2), 
				m_nRows(50), 
				m_nColumns(63), 
				m_cellWidth(11), 
				m_cellHeight(10),
				m_ssDisplaySurface(NULL),
				m_DrawBuffer(0),
				m_LogicBuffer(1)
{
	//allocate the array		
	m_grids = new bool**[m_nBuffers];				//creates an array of length m_nBuffers of pointers to pointers to bools
	for(int b = 0; b < m_nBuffers; b++)
	{
		m_grids[b] = new bool*[m_nRows];			//creates an array of length m_nRows of pointers to bools
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
				m_grids[b][r][c] = false;		// initialize all bools on both grids to be false
			}
		}
	}

	//load the file for the sprite sheet for a cell on the grid
	m_ssCellSprites = loadFile("sprites.png");

	// setup the offset for the display grid
	m_srDisplayOffset.x = 50;
	m_srDisplayOffset.y = 20;

	// setup the visible grid
	m_srDisplayGrid.x = m_srDisplayOffset.x;
	m_srDisplayGrid.y = m_srDisplayOffset.y;
	m_srDisplayGrid.w = 700;
	m_srDisplayGrid.h = 500;

	// setup the size of a cell
	m_srCellSpecs.x = 11;
	m_srCellSpecs.y = 10;
}

void Grid::Draw(SDL_Surface* Screen)
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
			//SDL_Rect tempRect = {(c * 10) + m_srDisplayOffset.x, (r * 10) + m_srDisplayOffset.y, 10, 10};

			//determine what color to fill the current cell with
			if(m_grids[m_DrawBuffer][r][c])
			{
				currentClip = alive;
			}
				
			else 
			{
				currentClip = dead;
			}

			//apply the current cell to the screen
			applySurface(m_srDisplayOffset.x, m_srDisplayOffset.y, m_ssCellSprites, Screen, &currentClip);  

			m_srDisplayOffset.x += m_cellWidth;	//increment horizontal offset
		}
		m_srDisplayOffset.x = 50;				// after drawing a horizontal line, reset horizontal offset
		m_srDisplayOffset.y += m_cellHeight;	// increment vertical offset
	}

	m_srDisplayOffset.y = 20;					// after drawing all vertical lines, reset vertical offset

	//return m_ssDisplaySurface;
}

bool Grid::HandleMouseInput(float x, float y)
{
	if(x >= m_srDisplayOffset.x && x <= m_srDisplayGrid.w + m_srDisplayOffset.x &&
		y >= m_srDisplayOffset.y && y <= m_srDisplayGrid.h + m_srDisplayOffset.y)
	{
	
		SDL_Rect cellPos;

		//determine the xy position of the cell that was clicked
		x -= m_srDisplayOffset.x;
		y -= m_srDisplayOffset.y;

		x /= m_srCellSpecs.x;
		y /= m_srCellSpecs.y;

		cellPos.x = (int)x;
		cellPos.y = (int)y;

		//if current cell is set to true, set it to false, else set it to true
		if(m_grids[0][cellPos.y][cellPos.x])
			m_grids[0][cellPos.y][cellPos.x] = false;
		else
			m_grids[0][cellPos.y][cellPos.x] = true;

		return true;
	}

	return false;
}

void Grid::Update()
{
	//this is only to be called when Game's m_isPlaying = true
	//responsible for going through game logic, and then afterwards switch the buffers DRAW and LOGIC

	//game logic


	//switch buffers
	if(m_DrawBuffer)
	{
		m_DrawBuffer = 0;
		m_LogicBuffer = 1;
	}
	else
	{
		m_DrawBuffer = 1;
		m_LogicBuffer = 0;
	}
}

Grid::~Grid()
{
	//deletes the array
	for(int b = 0; b < m_nBuffers; b++)
	{
		for(int r = 0; r < m_nRows; r++)
		{
			delete [] m_grids[b][r];
		}

		delete [] m_grids[b];
	}

	delete [] m_grids;

	SDL_FreeSurface(m_ssCellSprites);
}
