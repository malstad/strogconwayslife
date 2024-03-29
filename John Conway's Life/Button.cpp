#include "Button.h"


//parameterized constructor that takes in the button's offset from the origin of the screen
//also a bool that determines whether the button is the play button or the stop button
Button::Button()
{
	isPressed = false;
	SpriteSheet = NULL;

	//SpriteSheet = loadFile("buttons.png");

	//set the size and offset of each clip
	for(int i = 0; i < BUTTON_TYPES; i++)
	{
		m_srClip[i].h = 40;
		m_srClip[i].w = 80;
		m_srClip[i].x = 0;
		m_srClip[i].y = i * 40;
	}
}

bool Button::Initializer(int buttonType, int ScreenWidth, int ScreenHeight)
{
	//load the sprite sheet
	SpriteSheet = loadFile("buttons.bmp");
	if(NULL == SpriteSheet)
		return false;

	//set the type of the button (play, stop)
	type = buttonType;

	//set the size of the button's box
	width = 80;
	height = 40;
	yOffset = ScreenHeight - 70;

	//based on what type of button (play or stop), determines the position of the buttons
	if(buttonType == STOP_UNPRESSED)
	{

		xOffset = (ScreenWidth / 2) + width + 30; 
		
	}
	else
	{
		xOffset = ScreenWidth / 4;
	}

	return true;
}

void Button::Draw(SDL_Surface* Screen)
{
	applySurface(xOffset, yOffset, SpriteSheet, Screen, &m_srClip[type]);
}

bool Button::CheckIfPressed(float x, float y)
{
	if(x >= xOffset && x <= width + xOffset &&
		y >= yOffset && y <= height + yOffset)
		return true;

	else return false;
}

Button::~Button()
{
	SDL_FreeSurface(SpriteSheet);
}