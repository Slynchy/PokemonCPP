#include "SDL.h" // Main SDL library
#include <SDL_image.h> // SDL Image library
#include <SDL_ttf.h>
#include "src/SDLFunctions.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <string>

#define FPS 60

#define screenW 160
#define screenH 144

#define VIEWPORT_MOVEMENT_SPEED 0.05

struct Viewport
{
	int m_x;
	int m_y;
};
void Shutdown(std::vector<Zone> Zones,Player *player);
void DrawOverworld(SDL_Renderer *sdlRenderer, std::vector<Zone>& Zone_To_Draw,int scrW, int scrH, Player *player, Viewport *viewport);
double LinearInterpolate(double y1,double y2,double mu);
void UpdateViewport(Viewport *viewport, Player *player);

int main(int argc, char* argv[]) 
{

	Objects WorldObjects[5];
	WorldObjects[0].Init("Empty Collision Space", true);
	WorldObjects[1].Init("Grass", false);
	WorldObjects[2].Init();
	WorldObjects[3].Init();
	WorldObjects[4].Init("WarpSpace", false);

	SDL_Init( SDL_INIT_EVERYTHING );
	SDL_Window* screen;
	SDL_Renderer *sdlRenderer;
	SDL_Event events;
	//SDL_CreateWindowAndRenderer(screenW, screenH, SDL_WINDOW_RESIZABLE, &screen, &sdlRenderer);
	screen = SDL_CreateWindow("PokemonC++ Prototype", 600, 200, screenW, screenH, SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL);
    sdlRenderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(sdlRenderer, screenW, screenH);
	if( TTF_Init() == -1 )
    {
        return -1;    
    };
	const Uint8 *keyboardstate;

	Player player;
	player.Init(sdlRenderer);
	Keys keys;
	keys.Reset();

	Viewport viewport;
	viewport.m_x = (8 + (16 * player.m_x));
	viewport.m_y = (8 + (16 * player.m_y));

	std::vector<Zone> CURR_ZONES;
	Zone area_PalletTown;
	Zone area_Route1;
	CURR_ZONES.push_back(area_PalletTown);
	CURR_ZONES.push_back(area_Route1);
	CURR_ZONES[0].Init("pallet.png",sdlRenderer,"pallet.bin");
	CURR_ZONES[1].Init("route1.png",sdlRenderer,"route1.bin");

	Message HelloWorld;
	HelloWorld.Create("OAK: Its dangerous to go alone! Take this!");
	SDL_Texture *frame = IMG_LoadTexture(sdlRenderer, "text-frame.png");

	TTF_Font *font = NULL;
	font = TTF_OpenFont( "PokemonGB.ttf", 8);
	TTF_SetFontKerning(font, 0);
	TTF_SetFontHinting(font, TTF_HINTING_MONO);

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
			player.InBattle = true;
		};
		keys.Update(keyboardstate);
		
		SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255);
		SDL_RenderClear(sdlRenderer);	
		if(player.InBattle == false)
		{
			UpdateViewport(&viewport,&player);
			player.zoneIndex = CheckZone(CURR_ZONES,player.m_x,player.m_y);
			player.KeyboardInput(&keys,CURR_ZONES);
			DrawOverworld(sdlRenderer,CURR_ZONES,screenW,screenH, &player, &viewport);
		}
		else 
		{
			
		};
		//HelloWorld.Draw(sdlRenderer, frame, font);

		SDL_RenderPresent(sdlRenderer);
		keys.Reset();
		SDL_Delay(1000/FPS);
	};

	Shutdown(CURR_ZONES,&player);
    return 0;
}

void Shutdown(std::vector<Zone> Zones,Player *player)
{
	for(int i = 0; i < (unsigned char)Zones.size(); i++)
	{
		SDL_DestroyTexture(Zones[i].image);
	};
	SDL_DestroyTexture(player->spritesheet);
	Zones.clear();
	ShutdownSDL();
};

double LinearInterpolate(double y1,double y2,double mu)
{
	return(y1*(1-mu)+y2*mu);
}

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

void UpdateViewport(Viewport *viewport, Player *player)
{
	if(viewport->m_x != (8 + (16 * player->m_x)))
	{
		if(player->direction == RIGHT)
		{
			viewport->m_x = (int)ceil(LinearInterpolate(viewport->m_x,(int)(8 + (16 * player->m_x)),VIEWPORT_MOVEMENT_SPEED));
		} else {//if(player.direction == LEFT) {
			viewport->m_x = (int)floor(LinearInterpolate(viewport->m_x,(int)(8 + (16 * player->m_x)),VIEWPORT_MOVEMENT_SPEED));
		};
	};
	if(viewport->m_y != (8 + (16 * player->m_y)))
	{
		if(player->direction == DOWN)
		{
			viewport->m_y = (int)ceil(LinearInterpolate(viewport->m_y,(int)(8 + (16 * player->m_y)),VIEWPORT_MOVEMENT_SPEED));
		} else {//if(player.direction == UP) {
			viewport->m_y = (int)floor(LinearInterpolate(viewport->m_y,(int)(8 + (16 * player->m_y)),VIEWPORT_MOVEMENT_SPEED));
		};
	};
	if(viewport->m_x == (8 + (16 * player->m_x)) && viewport->m_y == (8 + (16 * player->m_y)))
	{
		// init pokebattle here
		player->m_moving = false;	
	};
	return;
};