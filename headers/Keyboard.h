#include "SDL.h"

struct Keys 
{
	bool W;
	bool S;
	bool A;
	bool D;
	void Reset(){W = false;S = false;A = false;D = false;};
	void Update(const Uint8* state)
	{
		W = (bool)state[SDL_SCANCODE_W];
		S = (bool)state[SDL_SCANCODE_S];
		A = (bool)state[SDL_SCANCODE_A];
		D = (bool)state[SDL_SCANCODE_D];
		return;
	};
};