#include <SDL.h>
#include <SDL_image.h>
#include <iostream>


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
	MainMenuStates MENUSTATE;
public:
	
	int Load(SDL_Renderer* sdlRenderer);
	void Draw(SDL_Renderer* sdlRenderer);


	MainMenuStates GetState()
	{
		return MENUSTATE;
	};
	MainMenu(void)
	{
		MENUSTATE = COPYRIGHTS;
	};
};