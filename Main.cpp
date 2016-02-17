#include "SDL.h" // Main SDL library
#include <SDL_image.h> // SDL Image library
#include "src/SDLFunctions.h"
#include "Player.h"
#include "Battle.h"
#include "MainMenu.h"

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <random>

#define FPS 60

#define screenW 160
#define screenH 144

#define VIEWPORT_MOVEMENT_SPEED 0.05

LoadedPokeSprites LoadedPokemonSprites;

PokedexPokemon POKEDEX_REFERENCE[151];

struct Viewport
{
	int m_x;
	int m_y;
};

enum GameStates
{
	MAIN_MENU,
	INGAME
};

void Shutdown(std::vector<Zone>,Player *, BattleScreen *);
void DrawOverworld(SDL_Renderer *sdlRenderer, std::vector<Zone>& Zone_To_Draw,int scrW, int scrH, Player *player, Viewport *viewport);
void DrawBattle(SDL_Renderer*, Player*, Battle*,BattleScreen*, SDL_Texture*, SDL_Texture*);
void UpdateViewport(Viewport *viewport, Player *player, Battle * _currentBattle);
void DrawNumber(unsigned char, int, int, SDL_Texture*, SDL_Renderer*, bool);

int main(int argc, char* argv[]) 
{
	srand(time(NULL));
	std::cout << "Size of Pokemon data structure (target is 43b): " << sizeof(Pokemon) << std::endl;
	GameStates GAMESTATE = MAIN_MENU;

	bool ANY_KEY_PRESSED = false;

	printf("Initializing WorldObjects...\n");
	Objects WorldObjects[8];
	WorldObjects[0].Init("Empty Collision Space", true);
	WorldObjects[1].Init("Grass", false);
	WorldObjects[2].Init();
	WorldObjects[3].Init();
	WorldObjects[4].Init("WarpSpace", false);
	WorldObjects[5].Init("Trainer1", true);
	WorldObjects[6].Init("Trainer2", true);
	WorldObjects[7].Init("Trainer3", true);
	
	printf("Initializing SDL...\n");
	SDL_Init( SDL_INIT_EVERYTHING );
	SDL_Window* screen;
	SDL_Renderer *sdlRenderer;
	SDL_Event events;
	screen = SDL_CreateWindow("PokemonC++ Prototype", 600, 200, screenW, screenH, SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL);
    sdlRenderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(sdlRenderer, screenW, screenH);
	const Uint8 *keyboardstate;

	printf("Initializing PokeDex...");
	LoadPokedexData();
	
	printf("Initializing MainMenu...\n");
	MainMenu* mainMenu = new MainMenu;
	if(mainMenu->Load(sdlRenderer) == -1)
		return -1;
	
	printf("Initializing Player...\n");
	Player* player = new Player(sdlRenderer);

	printf("Initializing Keys...\n");
	Keys keys;
	keys.Init();

	printf("Loading Pokemon front/back sprites...\n");
	if(LoadPokemonFrontSprites(sdlRenderer,&LoadedPokemonSprites) == -1 || LoadPokemonBackSprites(sdlRenderer,&LoadedPokemonSprites) == -1)
	{
		return -1;
	};

	Viewport viewport;
	viewport.m_x = (8 + (16 * player->m_x));
	viewport.m_y = (8 + (16 * player->m_y));
	
	printf("Initializing Zones...\n");
	std::vector<Zone> CURR_ZONES;
	Zone area_indigo;
	CURR_ZONES.push_back(area_indigo);
	CURR_ZONES[0].Init("indigoplateau.png",sdlRenderer,"indigoplateau.bin");
	
	printf("Loading text...\n");
	SDL_Texture* numbers = IMG_LoadTexture(sdlRenderer, "numbers.png");
	SDL_Texture* UpperCaseFont = IMG_LoadTexture(sdlRenderer, "UpperCaseFont.png");

	Pokemon opponent;
	Pokemon playerpoke = CreatePokemon((POKEMON_IDS)(81));
	PokeEngine::LevelUpBy(&playerpoke, 24);
	//playerpoke.StatusCond = POISON_COND;
	player->GetParty()->InsertPokemon(&playerpoke);
	
	printf("Initializing Battle...\n");
	Battle* currentBattle;
	BattleScreen* BattleSprites = new BattleScreen;
	if(BattleSprites->Load(sdlRenderer) == -1)
	{
		return -1;	
	};

	bool quit = false;
	while( !quit )
	{
		while( SDL_PollEvent( &events ) )
		{
			switch( events.type )
			{
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					ANY_KEY_PRESSED = true;
					break;
				default:
					break;
			}
		};
		keyboardstate = SDL_GetKeyboardState(NULL);
		if(keyboardstate[SDL_SCANCODE_ESCAPE])
		{
			quit=true;
		};
		if(keyboardstate[SDL_SCANCODE_SPACE])
		{
			player->SetInBattle(true);
		//	opponent = CreatePokemon((POKEMON_IDS)rand()%150);
			currentBattle = new Battle(player->GetParty(), new PokeParty(&CreatePokemon((POKEMON_IDS)(81)),&CreatePokemon((POKEMON_IDS)(81))));
		};
		keys.Timer++;
		if(keys.Timer >= 15 || player->GetInBattle() == false)
		{
			keys.Update(keyboardstate);
		};
		SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255);
		SDL_RenderClear(sdlRenderer);	
		switch (GAMESTATE)
		{
			case MAIN_MENU:
				mainMenu->Draw(sdlRenderer, LoadedPokemonSprites.POKEMON_FRONT_SPRITES);
				if(ANY_KEY_PRESSED == true)
				{
					GAMESTATE = INGAME;
					delete mainMenu;
				};
				break;
			case INGAME:
				if(player->GetInBattle() == false)
				{
					UpdateViewport(&viewport, player, currentBattle);
					player->zoneIndex = CheckZone(CURR_ZONES,player->m_x,player->m_y);
					player->KeyboardInput(&keys,CURR_ZONES);
					DrawOverworld(sdlRenderer,CURR_ZONES,screenW,screenH, player, &viewport);
					if(player->IsBattleScheduled())
					{
						player->SetInBattle(true);
						currentBattle = new Battle(player->GetParty(), new PokeParty(&CreatePokemon((POKEMON_IDS)(81)),&CreatePokemon((POKEMON_IDS)(81))));
						player->SetIsBattleScheduled(false);
					};
				}
				else 
				{
					currentBattle->Logic(&keys,player);
					if(player->GetInBattle() == true)
					{
						DrawBattle(sdlRenderer, player, currentBattle, BattleSprites, numbers, UpperCaseFont);
					};
				};
				break;
			default:
				break;
		};
		SDL_RenderPresent(sdlRenderer);
		keys.Reset();
		ANY_KEY_PRESSED = false;
		SDL_Delay(1000/FPS);
	};

	Shutdown(CURR_ZONES,player,BattleSprites);
    return 0;
}

void Shutdown(std::vector<Zone> Zones,Player *player, BattleScreen *BattleSprites)
{
	for(int i = 0; i < (unsigned char)Zones.size(); i++)
	{
		SDL_DestroyTexture(Zones[i].image);
	};
	SDL_DestroyTexture(player->spritesheet);
	BattleSprites->Shutdown();
	Zones.clear();
	delete player;
	ShutdownSDL();
};

void DrawBattle(SDL_Renderer *sdlRenderer, Player *_player, Battle *_currentBattle, BattleScreen *_battleSprites, SDL_Texture* _number_sprites, SDL_Texture* UpperCaseFont)
{
	SDL_RenderCopy(sdlRenderer, _battleSprites->OpponentInfo,NULL,NULL);
	int WidthOfHealthBar = (float)((float)( ( (float)_currentBattle->pokemon.CurrHP) / ( (float) _currentBattle->pokemon.MaxHP ) ) * 48);
	SDL_Rect OpponentPokeHealthBar_Rect = {32, 20, WidthOfHealthBar, 2};
	SDL_RenderCopy(sdlRenderer, _battleSprites->HPBar,NULL,&OpponentPokeHealthBar_Rect);
	SDL_RenderCopy(sdlRenderer, _battleSprites->PlayerInfo,NULL,NULL);
	WidthOfHealthBar = (float)((float)( ( (float)_currentBattle->GetActivePokemon().CurrHP) / ( (float)_currentBattle->GetActivePokemon().MaxHP ) ) * 48);
	SDL_Rect PlayerPokeHealthBar_Rect = {96, 76, WidthOfHealthBar, 2};
	SDL_RenderCopy(sdlRenderer, _battleSprites->HPBar,NULL,&PlayerPokeHealthBar_Rect);

	
	DrawStaticText(pokemon_names[_currentBattle->pokemon.Index], 8,0,sdlRenderer,UpperCaseFont);
	DrawStaticText(pokemon_names[_currentBattle->GetActivePokemon().Index], 80,56,sdlRenderer,UpperCaseFont);

	DrawNumber(_currentBattle->GetActivePokemon().CurrHP, 112, 81, _number_sprites, sdlRenderer, true);
	DrawNumber(_currentBattle->GetActivePokemon().MaxHP, 143, 81, _number_sprites, sdlRenderer, true);

	if(_currentBattle->GetActivePokemon().StatusCond == NONE)
	{
		DrawNumber(_currentBattle->GetActivePokemon().Level, 120, 65, _number_sprites, sdlRenderer, false);
	} else {
		DrawStaticText(StatusConditionStrings[_currentBattle->GetActivePokemon().StatusCond], 120,65,sdlRenderer,UpperCaseFont);
	};
	DrawNumber(_currentBattle->pokemon.Level, 40, 9, _number_sprites, sdlRenderer,false);

	SDL_Rect PlayerPokeBackSprite_Rect = {8,40,64,64}; //104, 16
	int w, h;
	SDL_QueryTexture(LoadedPokemonSprites.POKEMON_FRONT_SPRITES[_currentBattle->pokemon.Index], NULL, NULL, &w, &h);
	SDL_Rect OpponentPokeFrontSprite_Rect = {104,0,w,h}; //104, 16
	SDL_RenderCopy(sdlRenderer, LoadedPokemonSprites.POKEMON_BACK_SPRITES[_currentBattle->GetActivePokemon().Index],NULL,&PlayerPokeBackSprite_Rect);
	SDL_RenderCopy(sdlRenderer, LoadedPokemonSprites.POKEMON_FRONT_SPRITES[_currentBattle->pokemon.Index],NULL,&OpponentPokeFrontSprite_Rect);
	if(_currentBattle->MenuDepth <= 0)
	{
		SDL_RenderCopy(sdlRenderer, _battleSprites->Frame,NULL,NULL);

		SDL_Rect Arrow_Rect;
		Arrow_Rect.w = 7;
		Arrow_Rect.h = 7;
		switch (_currentBattle->SelectedMenuItem)
		{
			case 0:
				Arrow_Rect.x = 72;
				Arrow_Rect.y = 114;
				break;
			case 1:
				Arrow_Rect.x = 120;
				Arrow_Rect.y = 114;
				break;
			case 2:
				Arrow_Rect.x = 72;
				Arrow_Rect.y = 130;
				break;
			case 3:
				Arrow_Rect.x = 120;
				Arrow_Rect.y = 130;
				break;
			default:
				Arrow_Rect.x = 72;
				Arrow_Rect.y = 114;
				break;
		};
		SDL_RenderCopy(sdlRenderer, _battleSprites->arrow,NULL,&Arrow_Rect);
	}
	else
	{
		if(_currentBattle->SelectedMenuItem == 0 && _currentBattle->MenuDepth > 0) // fight
		{
			SDL_RenderCopy(sdlRenderer, _battleSprites->Frame_Fight,NULL,NULL);
			SDL_Rect Arrow_Rect;
			Arrow_Rect.w = 7;
			Arrow_Rect.h = 7;
			switch (_currentBattle->SelectedAttack)
			{
				case 0:
					Arrow_Rect.x = 40;
					Arrow_Rect.y = 106;
					break;
				case 1:
					Arrow_Rect.x = 40;
					Arrow_Rect.y = 114;
					break;
				case 2:
					Arrow_Rect.x = 40;
					Arrow_Rect.y = 122;
					break;
				case 3:
					Arrow_Rect.x = 40;
					Arrow_Rect.y = 130;
					break;
				default:
					Arrow_Rect.x = 40;
					Arrow_Rect.y = 106;
					break;
			};
			SDL_RenderCopy(sdlRenderer, _battleSprites->arrow,NULL,&Arrow_Rect);
			for(int i = 0; i < 4; i++)
			{
				DrawStaticText(MoveNames[_currentBattle->GetActivePokemon().MoveSet[i].Index], 49,106+(i*8),sdlRenderer,UpperCaseFont);
			};
			DrawNumber(_currentBattle->GetActivePokemon().MoveSet[_currentBattle->SelectedAttack].PP, 56,90, _number_sprites,sdlRenderer, true );
			DrawNumber(MOVES_ARRAY[_currentBattle->GetActivePokemon().MoveSet[_currentBattle->SelectedAttack].Index].PP, 64,90, _number_sprites,sdlRenderer, false );
		};
	};
};

void DrawOverworld(SDL_Renderer *sdlRenderer, std::vector<Zone>& Zone_To_Draw,int scrW, int scrH, Player *player, Viewport *viewport)
{
	SDL_Rect tempRect = {
		(viewport->m_x*-1)+(5*16),
		(viewport->m_y*-1)+(5*16),
		320,
		288};
	SDL_Rect tempRect2 = {
		viewport->m_x*-1,
		viewport->m_y*-1,
		144,
		120};
	for(int i = 0; i < (unsigned char)Zone_To_Draw.size(); i++)
	{
		SDL_Rect tempRect = {
			(viewport->m_x*-1)+(5*16)+(Zone_To_Draw[i].world_x*16),
			(viewport->m_y*-1)+(5*16)+(Zone_To_Draw[i].world_y*16),
			Zone_To_Draw[i].x_size * 16,
			Zone_To_Draw[i].y_size * 16};
		SDL_RenderCopyEx(sdlRenderer,Zone_To_Draw[i].image,NULL,&tempRect,0,NULL,SDL_FLIP_NONE);
	};
	player->Draw(sdlRenderer);
};

void UpdateViewport(Viewport *viewport, Player *player, Battle * _currentBattle)
{
	if(viewport->m_x != (8 + (16 * player->m_x)))
	{
		if(player->direction == RIGHT)
		{
			viewport->m_x = (int)ceil(PokeMath::LinearInterpolate(viewport->m_x,(int)(8 + (16 * player->m_x)),VIEWPORT_MOVEMENT_SPEED));
		} else {//if(player.direction == LEFT) {
			viewport->m_x = (int)floor(PokeMath::LinearInterpolate(viewport->m_x,(int)(8 + (16 * player->m_x)),VIEWPORT_MOVEMENT_SPEED));
		};
	};
	if(viewport->m_y != (8 + (16 * player->m_y)))
	{
		if(player->direction == DOWN)
		{
			viewport->m_y = (int)ceil(PokeMath::LinearInterpolate(viewport->m_y,(int)(8 + (16 * player->m_y)),VIEWPORT_MOVEMENT_SPEED));
		} else {//if(player.direction == UP) {
			viewport->m_y = (int)floor(PokeMath::LinearInterpolate(viewport->m_y,(int)(8 + (16 * player->m_y)),VIEWPORT_MOVEMENT_SPEED));
		};
	};
	if(viewport->m_x == (8 + (16 * player->m_x)) && viewport->m_y == (8 + (16 * player->m_y)))
	{
		// init pokebattle here
		/*if(player->m_moving == true)
		{
			int tempRand = (rand()%100);
			std::cout << tempRand << std::endl;
			if(tempRand > 90)
			{
				player->SetIsBattleScheduled(true);
			};
		};*/
		player->m_moving = false;	
	};
	return;
};

void DrawNumber(unsigned char _number_to_draw, int x, int y, SDL_Texture* numbers, SDL_Renderer* sdlRenderer, bool _leftorright)
{
	if(!_leftorright)
	{
		if(_number_to_draw < 10)
		{
			SDL_Rect temp1_SRC_Rect = {8*(_number_to_draw-1),0,8,8};
			SDL_Rect temp1_DST_Rect = {x,y,8,8};
			SDL_RenderCopy(sdlRenderer, numbers,&temp1_SRC_Rect,&temp1_DST_Rect);
		}
		else if(_number_to_draw < 100)
		{
			SDL_Rect temp1_SRC_Rect = {8*(floor(_number_to_draw/10)-1),0,8,8};
			SDL_Rect temp1_DST_Rect = {x,y,8,8};
			SDL_Rect temp2_SRC_Rect = {8*((_number_to_draw%10)-1),0,8,8};
			SDL_Rect temp2_DST_Rect = {x+8,y,8,8};
			if(temp2_SRC_Rect.x == -8)
				temp2_SRC_Rect.x = 8*9;
			SDL_RenderCopy(sdlRenderer, numbers,&temp1_SRC_Rect,&temp1_DST_Rect);
			SDL_RenderCopy(sdlRenderer, numbers,&temp2_SRC_Rect,&temp2_DST_Rect);
		}
		else 
		{
			SDL_Rect temp1_SRC_Rect = {8*(floor(_number_to_draw/100)-1),0,8,8};
			SDL_Rect temp1_DST_Rect = {x,y,8,8};
			SDL_Rect temp2_SRC_Rect = {8*((_number_to_draw%10)-1),0,8,8};
			SDL_Rect temp2_DST_Rect = {x+8,y,8,8};
			SDL_Rect temp3_SRC_Rect = {8*((_number_to_draw%100)-1),0,8,8};
			SDL_Rect temp3_DST_Rect = {x+16,y,8,8};
			if(temp2_SRC_Rect.x == -8)
				temp2_SRC_Rect.x = 8*9;
			if(temp3_SRC_Rect.x == -8)
				temp3_SRC_Rect.x = 8*9;
			SDL_RenderCopy(sdlRenderer, numbers,&temp1_SRC_Rect,&temp1_DST_Rect);
			SDL_RenderCopy(sdlRenderer, numbers,&temp2_SRC_Rect,&temp2_DST_Rect);
			SDL_RenderCopy(sdlRenderer, numbers,&temp3_SRC_Rect,&temp3_DST_Rect);
		};
	} 
	else 
	{
		if(_number_to_draw < 10)
		{
			SDL_Rect temp1_SRC_Rect = {8*(_number_to_draw-1),0,8,8};
			SDL_Rect temp1_DST_Rect = {x-8,y,8,8};
			SDL_RenderCopy(sdlRenderer, numbers,&temp1_SRC_Rect,&temp1_DST_Rect);
		}
		else if(_number_to_draw < 100)
		{
			SDL_Rect temp1_SRC_Rect = {8*(floor(_number_to_draw/10)-1),0,8,8};
			SDL_Rect temp1_DST_Rect = {x-16,y,8,8};
			SDL_Rect temp2_SRC_Rect = {8*((_number_to_draw%10)-1),0,8,8};
			SDL_Rect temp2_DST_Rect = {x-8,y,8,8};
			if(temp2_SRC_Rect.x == -8)
				temp2_SRC_Rect.x = 8*9;
			SDL_RenderCopy(sdlRenderer, numbers,&temp1_SRC_Rect,&temp1_DST_Rect);
			SDL_RenderCopy(sdlRenderer, numbers,&temp2_SRC_Rect,&temp2_DST_Rect);
		}
		else 
		{
			SDL_Rect temp1_SRC_Rect = {8*(floor(_number_to_draw/100)-1),0,8,8};
			SDL_Rect temp1_DST_Rect = {x-24,y,8,8};
			SDL_Rect temp2_SRC_Rect = {8*((_number_to_draw%10)-1),0,8,8};
			SDL_Rect temp2_DST_Rect = {x-16,y,8,8};
			SDL_Rect temp3_SRC_Rect = {8*((_number_to_draw%100)-1),0,8,8};
			SDL_Rect temp3_DST_Rect = {x-8,y,8,8};
			if(temp2_SRC_Rect.x == -8)
				temp2_SRC_Rect.x = 8*9;
			if(temp3_SRC_Rect.x == -8)
				temp3_SRC_Rect.x = 8*9;
			SDL_RenderCopy(sdlRenderer, numbers,&temp1_SRC_Rect,&temp1_DST_Rect);
			SDL_RenderCopy(sdlRenderer, numbers,&temp2_SRC_Rect,&temp2_DST_Rect);
			SDL_RenderCopy(sdlRenderer, numbers,&temp3_SRC_Rect,&temp3_DST_Rect);
		};
	};
};