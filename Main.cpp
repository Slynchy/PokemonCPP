#include "SDL.h" // Main SDL library
#include <SDL_image.h> // SDL Image library
#include <SDL_mixer.h> // SDL mixer library
#include "src/SDLFunctions.h"
#include "Player.h"
#include "Battle.h"
#include "MainMenu.h"

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <random>
#include <sstream>

#define FPS 60

#define screenW 160
#define screenH 144

#define VIEWPORT_MOVEMENT_SPEED 0.05

LoadedPokeSprites LoadedPokemonSprites;

PokedexPokemon POKEDEX_REFERENCE[151];

Player* player;
Battle* currentBattle;

short signed int PauseTimer = 0;

struct Viewport
{
	int m_x;
	int m_y;
};

enum GameStates
{
	MAIN_MENU,
	INGAME,
	GAME_WON
};

void Shutdown(std::vector<Zone>,Player *, BattleScreen *);
void DrawOverworld(SDL_Renderer *sdlRenderer, std::vector<Zone>& Zone_To_Draw,int scrW, int scrH, Player *player, Viewport *viewport);
void DrawBattle(SDL_Renderer*, Player*, Battle*,BattleScreen*, SDL_Texture*, SDL_Texture*, Keys*);
void UpdateViewport(Viewport *viewport, Player *player, Battle * _currentBattle);
void DrawNumber(short int, int, int, SDL_Texture*, SDL_Renderer*, bool);
void DrawPauseMenu(SDL_Renderer*, SDL_Texture*, Player*, Keys*, BattleScreen*, bool*, SDL_Texture*, SDL_Texture*);
void DrawPkmnSelectMenu(SDL_Renderer*, BattleScreen*, Player*, SDL_Texture*, SDL_Texture*, Keys*);
void DrawPokedex(SDL_Renderer*, BattleScreen*, Player*, SDL_Texture*, SDL_Texture*);
void ShutdownBattle(void);
void DrawItemMenu(SDL_Renderer*, BattleScreen*, Player*, SDL_Texture*, SDL_Texture*, Keys*);

int main(int argc, char* argv[]) 
{
	srand(unsigned int(time(NULL)));
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

	printf("Initializing Trainers...\n");
	Trainer* EliteFour[3];
	EliteFour[0] = new Trainer("Agatha", new PokeParty(new Pokemon(40,56),new Pokemon(43,56)));
	EliteFour[1] = new Trainer("Agatha", new PokeParty(new Pokemon(40,56),new Pokemon(43,56)));
	EliteFour[2] = new Trainer("Agatha", new PokeParty(
		new Pokemon(40,100,CONFUSE_RAY,NIGHT_SHADE,HYPNOSIS,DREAM_EATER),					// gengar
		new Pokemon(43,56, SUPERSONIC, CONFUSE_RAY, WING_ATTACK, HAZE),						// golbat
		new Pokemon(51,55, CONFUSE_RAY, NIGHT_SHADE, HYPNOSIS, DREAM_EATER),				// haunter 
		new Pokemon(3,58, BITE, GLARE, SCREECH, ACID),										// arbok
		new Pokemon(40,60, CONFUSE_RAY, NIGHT_SHADE, TOXIC, DREAM_EATER)					// Gengar
	));
	
	printf("Initializing SDL...\n");
	SDL_Init( SDL_INIT_EVERYTHING );
	SDL_Window* screen;
	SDL_Renderer *sdlRenderer;
	SDL_Event events;
	screen = SDL_CreateWindow("PokemonC++ Prototype", 600, 200, screenW, screenH, SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL);
    sdlRenderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(sdlRenderer, screenW, screenH);
	const Uint8 *keyboardstate;

	printf("Initializing SDL_mixer...\n");
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
	{
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
	}
	Mix_Music *battleMusic = NULL;
	Mix_Music *mainmenuMusic = NULL;
	mainmenuMusic = Mix_LoadMUS( "sfx/mainmenu.mp3" );
	battleMusic = Mix_LoadMUS( "sfx/battle.mp3" );
    if( mainmenuMusic == NULL || battleMusic == NULL)
    {
        printf( "Failed to load music! SDL_mixer Error: %s\n", Mix_GetError() );
    }
	Mix_VolumeMusic(MIX_MAX_VOLUME/4);

	printf("Initializing PokeDex...\n");
	LoadPokedexData();
	
	printf("Initializing MainMenu...\n");
	MainMenu* mainMenu = new MainMenu;
	if(mainMenu->Load(sdlRenderer) == -1)
		return -1;
	
	printf("Initializing Player...\n");
	player = new Player(sdlRenderer);
	player->m_x = 6;
	player->m_y = 32;
	SDL_Texture* pauseMenu = IMG_LoadTexture(sdlRenderer, "gfx/pause.png");

	printf("Initializing Keys...\n");
	Keys keys;
	keys.Init();

	printf("Loading Pokemon front/back sprites...\n");
	if(LoadPokemonFrontSprites(sdlRenderer,&LoadedPokemonSprites) == -1 || LoadPokemonBackSprites(sdlRenderer,&LoadedPokemonSprites) == -1)
	{
        printf( "Failed to load sprites!\n");
		return -1;
	};

	Viewport viewport;
	viewport.m_x = (8 + (16 * player->m_x));
	viewport.m_y = (8 + (16 * player->m_y));
	
	/*
		Initializing the zones, object data and
		image(s)
	*/
	printf("Initializing Zones...\n");
	std::vector<Zone> CURR_ZONES;
	Zone area_indigo;
	CURR_ZONES.push_back(area_indigo);
	CURR_ZONES[0].Init(sdlRenderer,"indigoplateau");
	
	/*
		Initializing font/number images
	*/
	printf("Loading text...\n");
	SDL_Texture* numbers = IMG_LoadTexture(sdlRenderer, "numbers.png");
	SDL_Texture* UpperCaseFont = IMG_LoadTexture(sdlRenderer, "UpperCaseFont.png");
	SDL_Texture* textBox = IMG_LoadTexture(sdlRenderer, "text-frame.png");
	
	/*
		This is to give the player
		some randomly generated pokemon...
		Not bothering to format/space out the parameters
		because they all are the same:
			(random pokeID, random level, random move from MOVES_ARRAY * 4)
	*/
	Pokemon playerpoke((POKEMON_IDS)(rand()%150),100,rand()%(sizeof(MOVES_ARRAY)/sizeof(*MOVES_ARRAY)),rand()%(sizeof(MOVES_ARRAY)/sizeof(*MOVES_ARRAY)),rand()%(sizeof(MOVES_ARRAY)/sizeof(*MOVES_ARRAY)),rand()%(sizeof(MOVES_ARRAY)/sizeof(*MOVES_ARRAY)));
	Pokemon playerpoke2((POKEMON_IDS)(rand()%150),100,rand()%(sizeof(MOVES_ARRAY)/sizeof(*MOVES_ARRAY)),rand()%(sizeof(MOVES_ARRAY)/sizeof(*MOVES_ARRAY)),rand()%(sizeof(MOVES_ARRAY)/sizeof(*MOVES_ARRAY)),rand()%(sizeof(MOVES_ARRAY)/sizeof(*MOVES_ARRAY)));
	Pokemon playerpoke3((POKEMON_IDS)(rand()%150),100,rand()%(sizeof(MOVES_ARRAY)/sizeof(*MOVES_ARRAY)),rand()%(sizeof(MOVES_ARRAY)/sizeof(*MOVES_ARRAY)),rand()%(sizeof(MOVES_ARRAY)/sizeof(*MOVES_ARRAY)),rand()%(sizeof(MOVES_ARRAY)/sizeof(*MOVES_ARRAY)));
	player->GetParty()->InsertPokemon(&playerpoke);
	player->GetParty()->InsertPokemon(&playerpoke2);
	player->GetParty()->InsertPokemon(&playerpoke3);
	
	/*
		This code loads the Battle data and
		inits currentBattle with dummy data
	*/
	printf("Initializing Battle...\n");
	currentBattle = new Battle(player, new PokeParty(&CreatePokemon((POKEMON_IDS)(81)),&CreatePokemon((POKEMON_IDS)(81))));
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
		if(keyboardstate[SDL_SCANCODE_SPACE])
		{
			player->activeMessage = new Message("HELLO");
		};
		keys.Timer++;
		PauseTimer++;
		if(keys.Timer >= 15 || (player->GetInBattle() == false && player->inPauseMenu == false) )
		{
			keys.Update(keyboardstate);
		};
		if(keyboardstate[SDL_SCANCODE_ESCAPE])
		{
			if(PauseTimer > 60)
			{
				PauseTimer = 0;
				if(player->inPauseMenu == false)
				{
					player->inPauseMenu = true;
				}
				else
				{
					player->inPauseMenu = false;
				};
			};
		};

		SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255);
		SDL_RenderClear(sdlRenderer);	
		switch (GAMESTATE)
		{
			case MAIN_MENU:
				mainMenu->Draw(sdlRenderer, LoadedPokemonSprites.POKEMON_FRONT_SPRITES);
				if( Mix_PlayingMusic() == 0 && mainMenu->GetState() == PRESS_START)
				{
					//Play the music
					Mix_PlayMusic( mainmenuMusic, -1 );
				}
				if(ANY_KEY_PRESSED == true)
				{
					if(mainMenu->GetState()==MainMenuStates::NEW_CONTINUE_GAME_OPTIONS)
					{
						GAMESTATE = INGAME;
						Mix_HaltMusic();
						delete mainMenu;
						player->activeMessage->Reset();
						break;
					} 
					else
					{
						mainMenu->SetState(MainMenuStates::NEW_CONTINUE_GAME_OPTIONS);
						player->activeMessage = new Message("BEAT THE ELITE THREE TO WIN!");
						SDL_Delay(1000/FPS);
					};
				};
				if(mainMenu->GetState()==MainMenuStates::NEW_CONTINUE_GAME_OPTIONS)
				{
					if(player->activeMessage->Active == true)
					{
						player->activeMessage->Update(sdlRenderer, textBox, UpperCaseFont, &keys);
					};
				};
				break;
			case INGAME:
				if(player->GetInBattle() == false)
				{
					if( Mix_PlayingMusic() == 0)
					{
						Mix_PlayMusic( CURR_ZONES[player->zoneIndex].music, -1 );
					}
					UpdateViewport(&viewport, player, currentBattle);
					player->zoneIndex = CheckZone(CURR_ZONES,player->m_x,player->m_y);
					if(!player->inPauseMenu && !player->activeMessage->Active)
					{
						player->KeyboardInput(&keys,CURR_ZONES);
					};
					DrawOverworld(sdlRenderer,CURR_ZONES,screenW,screenH, player, &viewport);
					if(player->inPauseMenu)
					{
						DrawPauseMenu(sdlRenderer, pauseMenu, player, &keys, BattleSprites, &quit, UpperCaseFont,numbers);
					};
					if(player->activeMessage->Active == true)
					{
						player->activeMessage->Update(sdlRenderer, textBox, UpperCaseFont, &keys);
						if(player->activeMessage->Active == false)
						{
							player->SetIsBattleScheduled(true);
						};
					};
					if(player->IsBattleScheduled())
					{
						player->SetInBattle(true);
						currentBattle = new Battle(player, EliteFour[player->currentOpponentID-1]->GetParty());
						currentBattle->PlayersTurn = true;
						player->SetIsBattleScheduled(false);
						Mix_HaltMusic();
						keys.Timer = -50;
						player->activeMessage->Reset();
					};
				}
				else 
				{
					if( Mix_PlayingMusic() == 0)
					{
						Mix_PlayMusic( battleMusic, -1 );
					}
					currentBattle->Logic(&keys,player, &quit);
					if(player->GetInBattle() == true)
					{
						DrawBattle(sdlRenderer, player, currentBattle, BattleSprites, numbers, UpperCaseFont, &keys);
						if(player->activeMessage->Active == true)
						{
							player->activeMessage->Update(sdlRenderer, textBox, UpperCaseFont, &keys);
						};
					};
				};
				break;
			case GAME_WON:
				// draw the three player pokemon here
				// draw a YOU WIN graphic
				// have a text box say "press any key to exit"
				break;
			default:
				break;
		};
		SDL_RenderPresent(sdlRenderer);
		keys.Reset();
		ANY_KEY_PRESSED = false;
		SDL_Delay(1000/FPS);
	};
	
    Mix_FreeMusic( mainmenuMusic );
	Mix_FreeMusic( battleMusic );
    battleMusic = NULL;
    mainmenuMusic = NULL;
	Shutdown(CURR_ZONES,player,BattleSprites);
    return 0;
}

void Shutdown(std::vector<Zone> Zones,Player *player, BattleScreen *BattleSprites)
{
	for(size_t i = 0; i < Zones.size(); i++)
	{
		SDL_DestroyTexture(Zones[i].image);
		Mix_FreeMusic( Zones[i].music );
		Zones[i].music = NULL;
	};
	SDL_DestroyTexture(player->spritesheet);
	BattleSprites->Shutdown();
	Zones.clear();
	delete player;
	ShutdownSDL();
};

void DrawBattle(SDL_Renderer *sdlRenderer, Player *_player, Battle *_currentBattle, BattleScreen *_battleSprites, SDL_Texture* _number_sprites, SDL_Texture* UpperCaseFont, Keys* _keys)
{
	SDL_RenderCopy(sdlRenderer, _battleSprites->OpponentInfo,NULL,NULL);
	int WidthOfHealthBar = int(((float)( ( (float)_currentBattle->pokemon.CurrHP) / ( (float) _currentBattle->pokemon.MaxHP ) ) * 48));
	SDL_Rect OpponentPokeHealthBar_Rect = {32, 20, WidthOfHealthBar, 2};
	SDL_RenderCopy(sdlRenderer, _battleSprites->HPBar,NULL,&OpponentPokeHealthBar_Rect);
	SDL_RenderCopy(sdlRenderer, _battleSprites->PlayerInfo,NULL,NULL);
	WidthOfHealthBar = int((float)( ( (float)_currentBattle->GetActivePokemon().CurrHP) / ( (float)_currentBattle->GetActivePokemon().MaxHP ) ) * 48);
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
		}
		else if(_currentBattle->SelectedMenuItem == 1 && _currentBattle->MenuDepth > 0)
		{
			DrawPkmnSelectMenu(sdlRenderer, _battleSprites, _player, UpperCaseFont, _number_sprites, _keys);
		}
		else if(_currentBattle->SelectedMenuItem == 2 && _currentBattle->MenuDepth > 0)
		{
			DrawItemMenu(sdlRenderer, _battleSprites, _player,UpperCaseFont,_number_sprites, _keys);
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

void DrawNumber(short int _number_to_draw, int x, int y, SDL_Texture* numbers, SDL_Renderer* sdlRenderer, bool _leftorright)
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
			SDL_Rect temp1_SRC_Rect = {8*int(floor(_number_to_draw/10)-1),0,8,8};
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
			SDL_Rect temp1_SRC_Rect = {8*int(floor(_number_to_draw/100)-1),0,8,8};
			SDL_Rect temp1_DST_Rect = {x,y,8,8};
			SDL_Rect temp2_SRC_Rect = {8*int( floor((_number_to_draw % 100) / 10 ) -1),0,8,8};
			SDL_Rect temp2_DST_Rect = {x+8,y,8,8};
			SDL_Rect temp3_SRC_Rect = {8*( (_number_to_draw % 10) - 1 ),0,8,8};
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
			SDL_Rect temp1_SRC_Rect = {8*int(floor(_number_to_draw/10)-1),0,8,8};
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
			SDL_Rect temp1_SRC_Rect = {8*int(floor(_number_to_draw/100)-1),0,8,8};
			SDL_Rect temp1_DST_Rect = {x-24,y,8,8};
			SDL_Rect temp2_SRC_Rect = {8*int( floor((_number_to_draw % 100) / 10 ) -1),0,8,8};
			SDL_Rect temp2_DST_Rect = {x-16,y,8,8};
			SDL_Rect temp3_SRC_Rect = {8* ( (_number_to_draw % 10) - 1 ),0,8,8};
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

void DrawPauseMenu(SDL_Renderer* _sdlRenderer, SDL_Texture* _pauseTex, Player* _player, Keys* _keys, BattleScreen* _battlescrn, bool* _quit, SDL_Texture* _upperCaseFont, SDL_Texture* _numberFont)
{
	if(_keys->S)
	{
		switch(_player->pauseMenuDepth)
		{
			case 0:
				if(_player->selectedPauseItem == 6)
				{
					_player->selectedPauseItem = 0;
				}
				else 
				{
					_player->selectedPauseItem++;
				};
				break;
			case 1:
				if(_player->selectedPauseItem == 0)
				{
					if(_player->selectedMenuItem >= 6)
					{
						_player->pokedexPage++;
						_player->selectedMenuItem = 0;
					}
					else
					{
						_player->selectedMenuItem++;
					};
				} 
				else 
				{
					//_player->selectedMenuItem++;
				};
				break;
			case 2:
				if(_player->selectedPauseItem == 0)
				{
					if(_player->selectedMenuItem2 >= 3)
					{
						//nothing
					}
					else
					{
						_player->selectedMenuItem2++;
					};
				};
				break;
			default:
				break;
		};
	}
	else if(_keys->W)
	{
		switch(_player->pauseMenuDepth)
		{
			case 0:
				if(_player->selectedPauseItem == 0)
				{
					_player->selectedPauseItem = 6;
				}
				else 
				{
					_player->selectedPauseItem--;
				};
				break;
			case 1:
				if(_player->selectedPauseItem == 0)
				{
					if(_player->selectedMenuItem <= 0)
					{
						if(_player->pokedexPage != 0)
						{
							_player->pokedexPage--;
							_player->selectedMenuItem = 6;
						};
					}
					else
					{
						_player->selectedMenuItem--;
					};
				} 
				else 
				{
					//_player->selectedMenuItem--;
				};
				break;
			case 2:
				if(_player->selectedPauseItem == 0)
				{
					if(_player->selectedMenuItem2 <= 0)
					{
						//nothing
					}
					else
					{
						_player->selectedMenuItem2--;
					};
				};
				break;
			default:
				break;
		};
	};
	if(_keys->A)
	{
		if(_player->pauseMenuDepth >= 1 && _player->selectedPauseItem == 0 && _player->pokedexPage > 0)
			_player->pokedexPage--;
	}
	else if(_keys->D)
	{
		if(_player->pauseMenuDepth >= 1 && _player->selectedPauseItem == 0)
			_player->pokedexPage++;
	};
	if(_keys->BACKSPACE && _player->pauseMenuDepth > 0)
	{
		_player->pauseMenuDepth--;
	};

	if(_keys->ENTER)
	{
		switch(_player->selectedPauseItem)
		{
			case 0:
				_player->pauseMenuDepth++;
				if(_player->pauseMenuDepth != 2)
					_player->selectedMenuItem = 0;
				break;
			case 1:
				_player->pauseMenuDepth++;
				_player->selectedMenuItem = 0;
				break;
			case 2:
				_player->pauseMenuDepth++;
				break;
			case 3:
				_player->pauseMenuDepth++;
				break;
			case 4:
				_player->pauseMenuDepth++;
				break;
			case 5:
				_player->pauseMenuDepth++;
				break;
			case 6:
				*_quit = true;
				break;
			default:
				break;
		};
	};

	SDL_Rect arrowRect = {87,15+(14*_player->selectedPauseItem),7,7};

	SDL_RenderCopy(_sdlRenderer, _pauseTex, NULL, NULL);
	SDL_RenderCopy(_sdlRenderer, _battlescrn->arrow, NULL, &arrowRect);
	if(_player->pauseMenuDepth > 0 && _player->selectedPauseItem == 2)
	{
		DrawItemMenu(_sdlRenderer, _battlescrn, _player,_upperCaseFont,_numberFont, _keys);
	};
	if(_player->pauseMenuDepth > 0 && _player->selectedPauseItem == 1)
	{
		DrawPkmnSelectMenu(_sdlRenderer, _battlescrn, _player,_upperCaseFont,_numberFont, _keys);
	};
	if(_player->pauseMenuDepth > 0 && _player->selectedPauseItem == 0)
	{
		DrawPokedex(_sdlRenderer, _battlescrn, _player,_upperCaseFont,_numberFont);
	};
	return;
};

void DrawPkmnSelectMenu(SDL_Renderer* _sdlRenderer, BattleScreen* _battleSprites, Player* _player, SDL_Texture* _upperCaseFont, SDL_Texture* _numberFont, Keys* _keys)
{
	if(_keys->S && currentBattle->MenuDepth < 2)
	{
		_player->selectedMenuItem++;
	}
	else if(_keys->W && currentBattle->MenuDepth < 2)
	{
		_player->selectedMenuItem--;
	};
	SDL_RenderCopy(_sdlRenderer, _battleSprites->pkmnSelectScreen, NULL, NULL);
	SDL_Rect arrowRect = {1,10+(16*_player->selectedMenuItem),7,7};
	SDL_RenderCopy(_sdlRenderer, _battleSprites->arrow, NULL, &arrowRect);
	int seperation = 16;
	for(size_t i = 0; i < _player->GetParty()->Party.size(); i++)
	{
		float WidthOfHealthBar = (float)((float)( ( (float)_player->GetParty()->Party[i].CurrHP) / ( (float)_player->GetParty()->Party[i].MaxHP ) ) * 48);
		SDL_Rect PlayerPokeHealthBar_Rect = {48, int(12+(seperation*i)), int(WidthOfHealthBar), 2};
		SDL_Rect PlayerPokeHealthBarOutline_Rect = {33, 11+(seperation*i), 64, 4};
		SDL_Rect LvlSlash = {104, 2+(seperation*i), 30, 14};
		SDL_Rect pkmn_icon = {8, 1+(seperation*i), 16, 16};
		SDL_RenderCopy(_sdlRenderer, _battleSprites->HPBar_Outline,NULL,&PlayerPokeHealthBarOutline_Rect);
		SDL_RenderCopy(_sdlRenderer, _battleSprites->HPBar,NULL,&PlayerPokeHealthBar_Rect);
		SDL_RenderCopy(_sdlRenderer, _battleSprites->lvlslash,NULL,&LvlSlash);
		SDL_RenderCopy(_sdlRenderer, _battleSprites->pkmn_icon,NULL,&pkmn_icon);
		DrawStaticText(pokemon_names[_player->GetParty()->Party[i].Index],24,0+(seperation*i),_sdlRenderer,_upperCaseFont);
		DrawNumber(_player->GetParty()->Party[i].Level,111,0+(seperation*i),_numberFont,_sdlRenderer, false);
		DrawNumber(_player->GetParty()->Party[i].CurrHP,126,8+(seperation*i),_numberFont,_sdlRenderer, true);
		DrawNumber(_player->GetParty()->Party[i].MaxHP,136,8+(seperation*i),_numberFont,_sdlRenderer, false);
	};
	if(currentBattle->MenuDepth > 1 && _player->GetInBattle() == true)
	{
		SDL_RenderCopy(_sdlRenderer, _battleSprites->pkmnselection_box,NULL,NULL);
	};

	return;
};

void DrawPokedex(SDL_Renderer* _sdlRenderer, BattleScreen* _battleSprites, Player* _player, SDL_Texture* _upperCaseFont, SDL_Texture* _numberFont)
{
	SDL_RenderCopy(_sdlRenderer, _battleSprites->pokedex, NULL, NULL);
	SDL_Rect arrowRect = {1,26+(16*_player->selectedMenuItem),7,7};
	SDL_RenderCopy(_sdlRenderer, _battleSprites->arrow, NULL, &arrowRect);

	for(int i = (0+(_player->pokedexPage * 7)); i < (7+(_player->pokedexPage * 7)); i++)
	{
		DrawStaticText(pokemon_names[i], 33, 25+((i-(_player->pokedexPage * 7))*16), _sdlRenderer, _upperCaseFont);
	};

	std::cout << "\n" << _player->pauseMenuDepth << "\n" <<_player->selectedMenuItem2;

	if(_player->pauseMenuDepth == 2)
	{
		SDL_Rect arrowRect = {121,80+(16*_player->selectedMenuItem2),7,7};
		SDL_RenderCopy(_sdlRenderer, _battleSprites->arrow, NULL, &arrowRect);
	} 
	else if(_player->pauseMenuDepth == 3 && _player->selectedMenuItem2 == 0)
	{
		SDL_RenderCopy(_sdlRenderer, _battleSprites->pokedexdetails, NULL, NULL);
	} 
	else if(_player->pauseMenuDepth == 3 && _player->selectedMenuItem2 == 3)
	{
		_player->pauseMenuDepth = 1;
		_player->selectedMenuItem2 = 0;
	};

	return;
};

void DrawItemMenu(SDL_Renderer* _sdlRenderer, BattleScreen* _battleSprites, Player* _player, SDL_Texture* _upperCaseFont, SDL_Texture* _numberFont, Keys* _keys)
{
	if(_keys->S && _player->pauseMenuDepth < 2)
	{
		_player->selectedMenuItem++;
	}
	else if(_keys->W && _player->pauseMenuDepth < 2)
	{
		_player->selectedMenuItem--;
	};
	SDL_RenderCopy(_sdlRenderer, _battleSprites->itemsMenu, NULL, NULL);
	SDL_Rect arrowRect = {40,34+(16*_player->selectedMenuItem),7,7};
	SDL_RenderCopy(_sdlRenderer, _battleSprites->arrow, NULL, &arrowRect);
	for(size_t i = 0; i < _player->m_inventory.size(); i++)
	{
		std::string temp = _player->m_inventory[i].m_name;
		DrawStaticText(temp, 48, 32+(i*16), _sdlRenderer, _upperCaseFont);
	};
	DrawStaticText("CANCEL", 48, 32+(_player->m_inventory.size()*16), _sdlRenderer, _upperCaseFont);
	if(_player->pauseMenuDepth > 1)
	{
		DrawPkmnSelectMenu(_sdlRenderer,_battleSprites,_player,_upperCaseFont,_numberFont,_keys);
	};
	return;
};

void ShutdownBattle(void)
{
	currentBattle->Shutdown(player);
	return;
};