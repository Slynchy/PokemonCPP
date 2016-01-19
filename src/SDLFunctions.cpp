#include "SDLFunctions.h"

int InitializeSDL(int scrW, int scrH, SDL_Renderer* sdlRenderer, SDL_Window* screen)
{
	if(SDL_Init( SDL_INIT_EVERYTHING ) != 0)
	{
		return -1;
	};
	if(SDL_CreateWindowAndRenderer(scrW, scrH, SDL_WINDOW_RESIZABLE, &screen, &sdlRenderer) != 0)
	{
		return -2;
	};
	if(SDL_RenderSetLogicalSize(sdlRenderer, scrW, scrH) != 0)
	{
		return -3;
	};
	return 0;
};

void ShutdownSDL()
{
    IMG_Quit();
    SDL_Quit();
};

SDL_Rect SDL_CreateRect(int x, int y, int w, int h)
{
	SDL_Rect temporaryRect = {x,y,w,h};
	return temporaryRect;
};