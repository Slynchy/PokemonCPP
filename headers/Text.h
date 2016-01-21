#include "Keyboard.h"
#include <string>
#include <iostream>
#include <SDL_image.h> // SDL Image library
#include <SDL_ttf.h>

struct Message
{
	std::string message;
	bool Active;
	float Frame;
	void Init();
	void Draw(SDL_Renderer *sdlRenderer, SDL_Texture *frame, TTF_Font *font);
	void Create(std::string _message);
};

SDL_Texture* renderText(const std::string &message, const std::string &fontFile,SDL_Color color, int fontSize, SDL_Renderer *renderer);