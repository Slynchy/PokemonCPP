#include "Text.h"

void Message::Init()
{
	Active = false;
	Frame = 0.0f;
	return;
};

void Message::Update(SDL_Renderer *sdlRenderer, SDL_Texture *frame, SDL_Texture *uppercaseFont, Keys *keys)
{
	SDL_Rect tempRect = {1, 144-46, 158, 46};
	SDL_RenderCopy(sdlRenderer, frame,NULL,&tempRect);
	if(Frame < strlen(message))
	{
		Frame += this->Speed;
	};
	size_t floorFrame = size_t(floor(Frame));
	for(size_t i = 0; i <= floorFrame; i++)
	{
		//bool line2 = false;
		if(i > strlen(message))
			break;
		std::string temp("");
		/*if(this->message[i] == '\n' || floorFrame > 15)
		{
			//line2 = true;
		};*/
		temp += this->message[i];
		if(i >= 15)
		{
			DrawStaticText(temp,10+(8*(i-15)),112+16,sdlRenderer,uppercaseFont);
		}
		else
		{
			DrawStaticText(temp,10+(8*i),112,sdlRenderer,uppercaseFont);
		};
	};

	if(keys->ENTER && Frame > (strlen(message)-2.0f))
	{
		Active = false;
		this->Complete = true;
		if(func != NULL)
		{
			func();		
		};
	};

	return;
};

void Message::Create(char* _message)
{
	Init();
	Frame = 0;
	Active = true;
	message = _message;
	return;
};

void DrawStaticText(std::string _text, int x, int y, SDL_Renderer* sdlRenderer, SDL_Texture* UpperCaseFont)
{
	const char* convertedText = _text.c_str();
	for(size_t i = 0; i < _text.length(); i++)
	{
	//	int temporaryInt = convertedText[i];
		SDL_Rect dstRect = {x+(8*i),y, 8,8};
		SDL_Rect srcRect = {((int)convertedText[i]-65)*8,0,8,8};
		SDL_RenderCopy(sdlRenderer, UpperCaseFont,&srcRect,&dstRect);
	};
};

void DrawStaticText(const char* _text, int x, int y, SDL_Renderer* sdlRenderer, SDL_Texture* UpperCaseFont)
{
	for(size_t i = 0; i < strlen(_text); i++)
	{
	//	int temporaryInt = convertedText[i];
		SDL_Rect dstRect = {x+(8*i),y, 8,8};
		SDL_Rect srcRect = {((int)_text[i]-65)*8,0,8,8};
		SDL_RenderCopy(sdlRenderer, UpperCaseFont,&srcRect,&dstRect);
	};
};