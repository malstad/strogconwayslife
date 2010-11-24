#ifndef MYSDLFUNCTIONS_H
#define MYSDLFUNCTIONS_H

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

bool init(SDL_Surface* &screen, int SCREEN_WIDTH, int SCREEN_HEIGHT, int SCREEN_BPP)
{
	//initialize all subsytems
	if(-1 == SDL_Init(SDL_INIT_EVERYTHING))
		return false;

	//initialize screen
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(NULL == screen)	//if there was an error, return false
		return false;

	SDL_WM_SetCaption("John Conway's Game of Life", NULL);

	return true;
}

SDL_Surface* loadImage(std::string sFileName, SDL_Color* key)
{
	SDL_Surface* loadedImage		= NULL;
	SDL_Surface* optimizedImage		= NULL;

	loadedImage = IMG_Load(sFileName.c_str());

	if(NULL != loadedImage)
	{
		optimizedImage = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);

		//sets color key as long as optimizing the image didn't fail and user didn't pass a NULL value for key
		if(NULL != optimizedImage && NULL != key)
		{
			Uint32 colorkey = SDL_MapRGB(optimizedImage->format, key->r, key->g, key->b);
			SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
		}
	}

	return optimizedImage;
}

SDL_Surface* loadFile(std::string fileName)		// uses loadImage
{
	SDL_Surface* image = NULL;

	image = loadImage(fileName, NULL);	//load sprites

	//check if process failed
	if(NULL == image)
	{
		return NULL;
	}

	return image;
}

void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, clip, destination, &offset);
}

#endif