#pragma once

#include "SDL.h" // Main SDL library
#include <SDL_image.h> // SDL Image library
#include <SDL_mixer.h> // SDL Image library

int Initialize_SDL(int scrW, int scrH, SDL_Renderer* sdlRenderer, SDL_Window* screen);

void ShutdownSDL();

SDL_Rect SDL_CreateRect(int x, int y, int w, int h);