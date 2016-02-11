#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "../src/SDLFunctions.h"
#include <iostream>
#include <vector>


enum MainMenuStates
{
	COPYRIGHTS,
	GAMEFREAK,
	INTRO,
	PRESS_START,
	NEW_CONTINUE_GAME_OPTIONS
};

class MainMenu
{
private:
	SDL_Texture* Copyrights_Sprite;
	SDL_Texture* Gamefreak_Intro;

	SDL_Texture* Pkmn_Logo;
	SDL_Texture* Trainer;
	SDL_Rect Trainer_Rect;
	SDL_Texture* PkmnBlu;

	int SelectedPkmn_index;

	MainMenuStates MENUSTATE;
	float Timer;

	SDL_Rect Pokemon_Logo_Rect;
	SDL_Rect Pokemon_Blue_Rect;
	SDL_Rect CurrentPKMN_Rect;
public:
	
	int Load(SDL_Renderer* sdlRenderer);
	void Draw(SDL_Renderer* sdlRenderer, std::vector<SDL_Texture*> _loadedfrontsprites);


	MainMenuStates GetState()
	{
		return MENUSTATE;
	};
	MainMenu(void)
	{
		MENUSTATE = COPYRIGHTS;
	};
};