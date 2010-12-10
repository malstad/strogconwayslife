#ifndef BUTTON_H
#define BUTTON_H

#include "MySDLFunctions.h"

enum ButtonTypes
{
	PLAY_UNPRESSED,
	PLAY_PRESSED,
	STOP_UNPRESSED,
	STOP_PRESSED,
	BUTTON_TYPES
};

class Button
{
private:
	int				xOffset, yOffset;
	int				width, height;
	int				type;
	bool			isPressed;
	SDL_Surface*	SpriteSheet;
	SDL_Rect		m_srClip[4];

public:
	Button();
	bool Initializer(int buttonType, int ScreenWidth, int ScreenHeight);
	void Draw(SDL_Surface* Screen);
	bool CheckIfPressed(float x, float y);
	~Button();

};

#endif