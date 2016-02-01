#include "MainMenu.h"


int MainMenu::Load(SDL_Renderer* sdlRenderer)
{
	Copyrights_Sprite = IMG_LoadTexture(sdlRenderer,"mainmenu/copyright.png");
	if(!Copyrights_Sprite)
	{
		printf("Failed to load copyright.png\n");
		return -1;
	};
	return 0;
};

void MainMenu::Draw(SDL_Renderer* sdlRenderer)
{
	SDL_Rect tempRect = {0,0,160,144};
	SDL_RenderCopy(sdlRenderer, MainMenu::Copyrights_Sprite,NULL,&tempRect);

	return;
};