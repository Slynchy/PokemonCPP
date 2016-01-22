#include "Keyboard.h"
#include <string>
#include <iostream>
#include <SDL_image.h> // SDL Image library
#include <SDL_ttf.h>

#ifndef TEXT_H
#define TEXT_H

struct Message
{
	std::string message;
	bool Active;
	float Frame;
	void Init();
	void Draw(SDL_Renderer *sdlRenderer, SDL_Texture *frame, TTF_Font *font);
	void Create(std::string _message);
};

void DrawStaticText(std::string _text, int x, int y, SDL_Renderer* sdlRenderer, SDL_Texture* UpperCaseFont);

#endif