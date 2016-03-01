#ifndef TEXT_H
#define TEXT_H

#include "Keyboard.h"
#include <string>
#include <iostream>
#include <SDL_image.h> // SDL Image library
#include <cstring>

#define TEXT_SPEED_DEFAULT 0.4f

class Battle;

struct Message
{
	char* message;
	bool Active;
	bool Complete;
	float Frame;
	float Speed;
	bool NewLine;
	void (*func)(void);
	void Init();
	void Update(SDL_Renderer *sdlRenderer, SDL_Texture *frame, SDL_Texture *uppercaseFont, Keys *keys);
	void Create(char* _message);
	Message(char* _mes)
	{
		this->message = _mes;
		this->Frame = 0.0f;
		this->Active = true;
		this->Speed = TEXT_SPEED_DEFAULT;
		this->func = NULL;
		this->Complete = false;
		this->NewLine = false;
	};
	Message(char* _mes, void (*_func)(void), float _speed)
	{
		this->message = _mes;
		this->Frame = 0.0f;
		this->Active = true;
		this->Speed = _speed;
		this->func = _func;
		this->NewLine = false;
		this->Complete = false;
	};
	Message(char* _mes, float _speed)
	{
		this->message = _mes;
		this->Frame = 0.0f;
		this->Active = true;
		this->Speed = _speed;
		this->Complete = false;
		this->func = NULL;
		this->NewLine = false;
	};
	inline void Reset()
	{
		this->message = "";
		this->Frame = 0.0f;
		this->Active = false;
		this->Speed = TEXT_SPEED_DEFAULT;
		this->Complete = false;
		this->func = NULL;
		this->NewLine = false;
	};
};

/* ONLY DRAWS CAPITAL LETTERS */
void DrawStaticText(std::string _text, int x, int y, SDL_Renderer* sdlRenderer, SDL_Texture* UpperCaseFont);
void DrawStaticText(const char* _text, int x, int y, SDL_Renderer* sdlRenderer, SDL_Texture* UpperCaseFont);

#endif