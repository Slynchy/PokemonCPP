#include "MainMenu.h"


int MainMenu::Load(SDL_Renderer* sdlRenderer)
{
	Timer = 0.0f;
	SelectedPkmn_index = rand()%150;
	Pokemon_Blue_Rect = SDL_CreateRect(224,64,64,8); // 56,64 dest
	Pokemon_Logo_Rect = SDL_CreateRect(16,-56,128,56); // 16,8 dest
	CurrentPKMN_Rect = SDL_CreateRect(216,96,56,56); // 48,96 dest 
	Trainer_Rect = SDL_CreateRect(82,80,40,56);

	Copyrights_Sprite = IMG_LoadTexture(sdlRenderer,"mainmenu/copyright.png");
	Gamefreak_Intro = IMG_LoadTexture(sdlRenderer,"mainmenu/gamefreak_intro.png");

	Pkmn_Logo = IMG_LoadTexture(sdlRenderer,"mainmenu/pokemon_logo.png");
	Trainer = IMG_LoadTexture(sdlRenderer,"mainmenu/player_title.png");
	PkmnBlu = IMG_LoadTexture(sdlRenderer,"mainmenu/blueversion.png");


	if(!Copyrights_Sprite || !Gamefreak_Intro || !Pkmn_Logo || !Trainer || !PkmnBlu)
	{
		printf("Failed to load a main menu png\n");
		return -1;
	};
	return 0;
};

void MainMenu::Draw(SDL_Renderer* sdlRenderer, std::vector<SDL_Texture*> _loadedfrontsprites)
{
	Timer += 0.016f;
	SDL_Rect tempRect = {0,0,160,144};
	switch(MENUSTATE)
	{
		case COPYRIGHTS:
			SDL_RenderCopy(sdlRenderer, MainMenu::Copyrights_Sprite,NULL,&tempRect);
			if(Timer > 2.0f)
			{
				MENUSTATE = GAMEFREAK;
				Timer = 0.0f;
			};

			break;
		case GAMEFREAK:
			SDL_RenderCopy(sdlRenderer, MainMenu::Gamefreak_Intro,NULL,&tempRect);
			if(Timer > 2.0f)
			{
				MENUSTATE = PRESS_START;
				Timer = 0.0f;
			};
			break;
		case PRESS_START:
			if(1==1)
			{
				if(Pokemon_Logo_Rect.y != 8)
				{
					Pokemon_Logo_Rect.y += 4;
				};
				if(Pokemon_Blue_Rect.x != 56)
				{
					Pokemon_Blue_Rect.x -= 4;
				};
				SDL_RenderCopy(sdlRenderer, MainMenu::Pkmn_Logo,NULL,&Pokemon_Logo_Rect);
				SDL_RenderCopy(sdlRenderer, MainMenu::PkmnBlu,NULL,&Pokemon_Blue_Rect);
				
				int w, h;
				SDL_QueryTexture(_loadedfrontsprites[SelectedPkmn_index], NULL, NULL, &w, &h);
				CurrentPKMN_Rect.w = w;
				CurrentPKMN_Rect.h = h;

				SDL_RenderCopy(sdlRenderer, _loadedfrontsprites[SelectedPkmn_index],NULL,&CurrentPKMN_Rect);
				SDL_RenderCopy(sdlRenderer, MainMenu::Trainer,NULL,&Trainer_Rect);
				if(CurrentPKMN_Rect.x > 48)
				{
					CurrentPKMN_Rect.x -= 2;
				} else {
					Timer += 0.016f;
					if(Timer > 6.0f)
					{
						if(CurrentPKMN_Rect.x > -56)
						{
							CurrentPKMN_Rect.x -= 2;
						} else {
							Timer = 0.0f;
							CurrentPKMN_Rect.x = 216;
							SelectedPkmn_index = rand()%150;
						};
					};
				};
			};
			break;
		default:
			break;
	};

	return;
};