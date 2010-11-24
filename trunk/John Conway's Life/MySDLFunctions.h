#ifndef MYSDLFUNCTIONS_H
#define MYSDLFUNCTIONS_H

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

bool init(SDL_Surface* &screen, int SCREEN_WIDTH, int SCREEN_HEIGHT, int SCREEN_BPP);
SDL_Surface* loadImage(std::string sFileName, SDL_Color* key);
SDL_Surface* loadFile(std::string fileName);
void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);

#endif