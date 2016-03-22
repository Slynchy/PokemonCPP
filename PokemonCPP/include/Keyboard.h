#include "SDL.h"

#ifndef KEYBOARD_H
#define KEYBOARD_H

struct Keys 
{
	bool W;
	bool S;
	bool A;
	bool D;
	bool ENTER;
	bool ESC;
	bool BACKSPACE;
	int Timer;
	void Reset(){W = false;S = false;A = false;D = false;BACKSPACE = false;ENTER = false;ESC = false;};
	void Init(){Reset();Timer = 0;};
	void Update(const Uint8* state)
	{
		W = (bool)state[SDL_SCANCODE_W];
		S = (bool)state[SDL_SCANCODE_S];
		A = (bool)state[SDL_SCANCODE_A];
		D = (bool)state[SDL_SCANCODE_D];
		ENTER = (bool)state[SDL_SCANCODE_RETURN];
		BACKSPACE = (bool)state[SDL_SCANCODE_BACKSPACE];
		ESC = (bool)state[SDL_SCANCODE_ESCAPE];
		if(W == true || S == true || A == true || D == true || BACKSPACE == true || ENTER == true || ESC == true)
			Timer = 0;
		return;
	};
};

#endif