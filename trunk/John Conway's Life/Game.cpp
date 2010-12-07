#include "Game.h"

Game::Game(): toQuit(false),
			  m_isPlaying(true),
			  m_ssScreen(NULL),
			  SCREEN_WIDTH(800),
			  SCREEN_HEIGHT(600),
			  SCREEN_BPP(32),
			  m_bPlay(PLAY_UNPRESSED, SCREEN_WIDTH, SCREEN_HEIGHT),
			  m_bStop(STOP_UNPRESSED, SCREEN_WIDTH, SCREEN_HEIGHT)
{
	if(!init(m_ssScreen, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP))
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
			float CoordX, CoordY;
			
			CoordX = m_seEvent.button.x;
			CoordY = m_seEvent.button.y;

			m_gCellGrid.HandleMouseInput(CoordX, CoordY);
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
	m_gCellGrid.Update();
	//m_bPlay.Update();
	//m_bStop.Update();

	//flip the screen
	SDL_Flip(m_ssScreen);
}