#include "SDL.h" // Main SDL library
#include <SDL_image.h> // SDL Image library
#include "src/SDLFunctions.h"
#include "Player.h"
#include <iostream>
#include <chrono>
#define FPS 60

#define screenW 160
#define screenH 144

#define VIEWPORT_MOVEMENT_SPEED 0.05

int palletTown_Collision[18][20] = //std::vector<int> levelTest[18][20] = 
{
	{-1,-1,-1,0,-1,-1,-1,-1,-1,0,-1,-1,0,-1,-1,-1,-1,-1,0,-1},
	{0,0,0,0,0,0,0,0,0,0,-1,-1,0,0,0,0,0,0,0,0},
	{0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0},
	{0,-1,-1,-1,0,0,0,0,-1,-1,-1,-1,0,0,0,0,-1,-1,-1,0},
	{0,-1,-1,-1,0,0,0,0,-1,-1,-1,-1,0,0,0,0,-1,-1,-1,0},
	{0,-1,-1,4,0,1,0,0,-1,-1,-1,4,0,1,0,0,-1,-1,-1,0},
	{0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0},
	{0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0},
	{0,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,-1,-1,-1,0},
	{0,-1,-1,-1,0,0,0,4,-1,-1,0,0,0,0,0,0,-1,-1,-1,0},
	{0,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,-1,-1,-1,0},
	{0,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,1,0,0,0,-1,-1,-1,0},
	{0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0},
	{0,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,4,0,0,-1,-1,-1,0},
	{0,-1,-1,-1,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0},
	{0,-1,-1,-1,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0},
	{0,-1,-1,-1,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0},
	{0,0,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

struct Viewport
{
	int m_x;
	int m_y;
};
void Shutdown(SDL_Texture *area_PalletTown);
void Draw(SDL_Renderer *sdlRenderer, SDL_Texture *palletTown,int scrW, int scrH, Player *player, Viewport *viewport);
double LinearInterpolate(double y1,double y2,double mu);

int main(int argc, char* argv[]) 
{
	SDL_Init( SDL_INIT_EVERYTHING );
	SDL_Window* screen;
	SDL_Renderer *sdlRenderer;
	SDL_Event events;
	//SDL_CreateWindowAndRenderer(screenW, screenH, SDL_WINDOW_RESIZABLE, &screen, &sdlRenderer);
	screen = SDL_CreateWindow("PokemonCPP Prototype", 600, 200, screenW*3, screenH*3, SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL);
    sdlRenderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(sdlRenderer, screenW, screenH);
	const Uint8 *keyboardstate;

	SDL_GLContext context;
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 4);			// 16-bit colour depth
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);		// Automatic Double Buffering
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);	// Hardware acceleration
	context = SDL_GL_CreateContext(screen);
	if (!context) 
	{
		fprintf(stderr, "Couldn't create context: %s\n", SDL_GetError());
		return -1;
	}

	Player player;
	player.Init(sdlRenderer);

	Viewport viewport;
	viewport.m_x = (8 + (16 * player.m_x));
	viewport.m_y = (8 + (16 * player.m_y));

	SDL_Texture *area_PalletTown;
	area_PalletTown = IMG_LoadTexture(sdlRenderer,  "pallet.png");
	if(!area_PalletTown)
	{
		fprintf(stderr, "Couldn't load texture: %s\n", SDL_GetError());
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

				default:
					break;
			}
		};
		std::cout << palletTown_Collision[player.m_y][player.m_x] << std::endl;
		keyboardstate = SDL_GetKeyboardState(NULL);
		if(keyboardstate[SDL_SCANCODE_ESCAPE])
		{
			quit=true;
		};

		//std::cout << std::endl << viewport.m_x << std::endl << (8 + (16 * player.m_x)) << std::endl;
		if(viewport.m_x != (8 + (16 * player.m_x)))
		{
			if(player.direction == RIGHT)
			{
				viewport.m_x = (int)ceil(LinearInterpolate(viewport.m_x,(int)(8 + (16 * player.m_x)),VIEWPORT_MOVEMENT_SPEED));
			} else {//if(player.direction == LEFT) {
				viewport.m_x = (int)floor(LinearInterpolate(viewport.m_x,(int)(8 + (16 * player.m_x)),VIEWPORT_MOVEMENT_SPEED));
			};
		};
		if(viewport.m_y != (8 + (16 * player.m_y)))
		{
			if(player.direction == DOWN)
			{
				viewport.m_y = (int)ceil(LinearInterpolate(viewport.m_y,(int)(8 + (16 * player.m_y)),VIEWPORT_MOVEMENT_SPEED));
			} else {//if(player.direction == UP) {
				viewport.m_y = (int)floor(LinearInterpolate(viewport.m_y,(int)(8 + (16 * player.m_y)),VIEWPORT_MOVEMENT_SPEED));
			};
		};
		if(viewport.m_x == (8 + (16 * player.m_x)) && viewport.m_y == (8 + (16 * player.m_y)))
		{
			player.m_moving = false;	
		};

		player.KeyboardInput(keyboardstate,palletTown_Collision);
		Draw(sdlRenderer,area_PalletTown,screenW,screenH, &player, &viewport);
		SDL_RenderPresent(sdlRenderer);
		SDL_Delay(1000/FPS);
	};

	Shutdown(area_PalletTown);
    return 0;
}

void Shutdown(SDL_Texture *area_PalletTown)
{
	SDL_DestroyTexture(area_PalletTown);
	ShutdownSDL();
};

double LinearInterpolate(double y1,double y2,double mu)
{
	return(y1*(1-mu)+y2*mu);
}

void Draw(SDL_Renderer *sdlRenderer, SDL_Texture *palletTown,int scrW, int scrH, Player *player, Viewport *viewport)
{
	SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
	SDL_RenderClear(sdlRenderer);	
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
	SDL_RenderCopyEx(sdlRenderer,palletTown,NULL,&tempRect,0,NULL,SDL_FLIP_NONE);
	//SDL_RenderCopy(sdlRenderer,palletTown,NULL,&tempRect);
	player->Draw(sdlRenderer);
};