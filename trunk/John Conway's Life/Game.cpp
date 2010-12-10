#include "Game.h"

Game::Game(): toQuit(false),
			  m_isPlaying(false),
			  m_bMouseDown(false),
			  m_ssScreen(NULL),
			  SCREEN_WIDTH(800),
			  SCREEN_HEIGHT(600),
			  SCREEN_BPP(32)
{
	//initialize screen
	m_ssScreen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(NULL == m_ssScreen)	//if there was an error, flag program to quit
		toQuit = true;

	if(!m_gCellGrid.Initializer())
		toQuit = true;
	if(!m_bPlay.Initializer(PLAY_UNPRESSED, SCREEN_WIDTH, SCREEN_HEIGHT))
		toQuit = true;
	if(!m_bStop.Initializer(STOP_UNPRESSED, SCREEN_WIDTH, SCREEN_HEIGHT))
		toQuit = true;
}

void Game::Draw()
{
	m_gCellGrid.Draw(m_ssScreen);
	m_bPlay.Draw(m_ssScreen);
	m_bStop.Draw(m_ssScreen);
}

void Game::HandleInput()
{
	while(SDL_PollEvent(&m_seEvent))
	{
		// if user has opted to quit
		if(m_seEvent.type == SDL_QUIT)
		{
			toQuit = true; // flags program to quit 
		}

		// if the user left clicks
		if(m_seEvent.type == SDL_MOUSEBUTTONDOWN && m_seEvent.button.button == SDL_BUTTON_LEFT)
		{
			m_bMouseDown = true;
		}

		else if(m_seEvent.type == SDL_MOUSEBUTTONUP && m_seEvent.button.button == SDL_BUTTON_LEFT)
		{
			m_bMouseDown = false;
		}

		if(m_bMouseDown)
		{
			float CoordX, CoordY;
			
			CoordX = m_seEvent.button.x;
			CoordY = m_seEvent.button.y;

			if(!m_gCellGrid.HandleMouseInput(CoordX, CoordY))
			{
				m_bMouseDown = false;
			}
			if(m_bPlay.CheckIfPressed(CoordX, CoordY))
				m_isPlaying = true;
			else if(m_bStop.CheckIfPressed(CoordX, CoordY))
				m_isPlaying = false;
		}
	}
}

void Game::Update()
{
	//updates all drawn objects to the screen
	if(m_isPlaying)
		m_gCellGrid.Update();

	//flip the screen
	SDL_Flip(m_ssScreen);
}