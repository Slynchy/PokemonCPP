#include "Text.h"

void Message::Init()
{
	Active = false;
	Frame = 0.0f;
	return;
};

void Message::Draw(SDL_Renderer *sdlRenderer, SDL_Texture *frame, TTF_Font *font)
{
	SDL_Rect tempRect = {1, 144-46, 158, 46};
	SDL_RenderCopy(sdlRenderer, frame,NULL,&tempRect);
	SDL_Color textColor = { 0, 0, 0 };
	SDL_Rect tempRect2 = {8, 106, 143, 36};
	SDL_Surface *testsurf = TTF_RenderText_Blended_Wrapped( font, message.c_str(), textColor, 143);
	SDL_Texture *testTex = SDL_CreateTextureFromSurface(sdlRenderer, testsurf);
	SDL_RenderCopy(sdlRenderer, testTex,NULL,&tempRect2);
	return;
};

void Message::Create(std::string _message)
{
	Init();
	Frame = 0;
	Active = true;
	message = _message;
	return;
};