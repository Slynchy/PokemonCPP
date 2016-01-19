#include "Player.h"

void Animation::init(int f1_x, int f1_y, SDL_RendererFlip f1_flip,int f2_x, int f2_y, SDL_RendererFlip f2_flip)
{
	this->frames.push_back(SDL_CreateRect(f1_x,f1_y,16,16));
	this->frames.push_back(SDL_CreateRect(f2_x,f2_y,16,16));
	this->flip_Flag.push_back(f1_flip);
	this->flip_Flag.push_back(f2_flip);
};

void Animation::init(int f1_x, int f1_y, SDL_RendererFlip f1_flip,int f2_x, int f2_y, SDL_RendererFlip f2_flip, int f3_x, int f3_y, SDL_RendererFlip f3_flip)
{
	this->frames.push_back(SDL_CreateRect(f1_x,f1_y,16,16));
	this->frames.push_back(SDL_CreateRect(f2_x,f2_y,16,16));
	this->frames.push_back(SDL_CreateRect(f3_x,f3_y,16,16));
	this->flip_Flag.push_back(f1_flip);
	this->flip_Flag.push_back(f2_flip);
	this->flip_Flag.push_back(f3_flip);
};

void Animation::init(int f1_x, int f1_y, SDL_RendererFlip f1_flip,int f2_x, int f2_y, SDL_RendererFlip f2_flip, int f3_x, int f3_y, SDL_RendererFlip f3_flip, int f4_x, int f4_y, SDL_RendererFlip f4_flip)
{
	this->frames.push_back(SDL_CreateRect(f1_x,f1_y,16,16));
	this->frames.push_back(SDL_CreateRect(f2_x,f2_y,16,16));
	this->frames.push_back(SDL_CreateRect(f3_x,f3_y,16,16));
	this->frames.push_back(SDL_CreateRect(f4_x,f4_y,16,16));
	this->flip_Flag.push_back(f1_flip);
	this->flip_Flag.push_back(f2_flip);
	this->flip_Flag.push_back(f3_flip);
	this->flip_Flag.push_back(f4_flip);
};

void Player::KeyboardInput(const Uint8 *keyboardstate, int (&levelCollisionArray)[18][20])
{
	if(!Player::m_moving){
		if(keyboardstate[SDL_SCANCODE_W])
		{
			direction = UP;
			Player::m_moving = true;
			if(Player::CheckCollision(levelCollisionArray,Player::m_x,Player::m_y-1) == false)
			{
				Player::m_y -= 1;
			};
		} else if(keyboardstate[SDL_SCANCODE_S])
		{
			direction = DOWN;
			Player::m_moving = true;
			if(Player::CheckCollision(levelCollisionArray,Player::m_x,Player::m_y+1) == false)
			{
				Player::m_y += 1;
			};
		} else if(keyboardstate[SDL_SCANCODE_A])
		{
			direction = LEFT;
			Player::m_moving = true;
			if(Player::CheckCollision(levelCollisionArray,Player::m_x-1,Player::m_y) == false)
			{
				Player::m_x -= 1;
			};
		} else if(keyboardstate[SDL_SCANCODE_D])
		{
			direction = RIGHT;
			Player::m_moving = true;
			if(Player::CheckCollision(levelCollisionArray,Player::m_x+1,Player::m_y) == false)
			{
				Player::m_x += 1;
			};
		};
	};
	return;
};

void Player::Draw(SDL_Renderer *sdlRenderer)
{
	SDL_Rect tempRect2 = SDL_CreateRect(160/2-8,144/2,16,16);
	if(!m_moving)
	{
		animationFrame = 0;
		animationFrame2 = 0;
		switch(direction)
		{
			case LEFT:
				SDL_RenderCopyEx(sdlRenderer,spritesheet,&standingLeftRight_SpriteRect,&tempRect2,0,NULL,SDL_FLIP_NONE);
				break;
			case RIGHT:
				SDL_RenderCopyEx(sdlRenderer,spritesheet,&standingLeftRight_SpriteRect,&tempRect2,0,NULL,SDL_FLIP_HORIZONTAL);
				break;
			case UP:
				SDL_RenderCopyEx(sdlRenderer,spritesheet,&standingUp_SpriteRect,&tempRect2,0,NULL,SDL_FLIP_NONE);
				break;
			case DOWN:
				SDL_RenderCopyEx(sdlRenderer,spritesheet,&standingDown_SpriteRect,&tempRect2,0,NULL,SDL_FLIP_NONE);
				break;
		};
	}
	else
	{
		if(++animationFrame >= 40)
		{
			animationFrame = 0;
		};
		if(++animationFrame2 >= 20)
		{
			animationFrame2 = 0;
		};
		switch(direction)
		{
			case LEFT:
				SDL_RenderCopyEx(sdlRenderer,spritesheet,&walkingLeftRight.frames[((int)ceil(float(animationFrame2/10)))],&tempRect2,0,NULL,SDL_FLIP_NONE);
				break;
			case RIGHT:
				SDL_RenderCopyEx(sdlRenderer,spritesheet,&walkingLeftRight.frames[((int)floor(float(animationFrame2/10)))],&tempRect2,0,NULL,SDL_FLIP_HORIZONTAL);
				break;
			case UP:
				SDL_RenderCopyEx(sdlRenderer,spritesheet,&walkingUp.frames[(int)floor(float(animationFrame/10))],&tempRect2,0,NULL,walkingUp.flip_Flag[(int)floor(float(animationFrame/10))]);
				break;
			case DOWN:
				SDL_RenderCopyEx(sdlRenderer,spritesheet,&walkingDown.frames[(int)floor(float(animationFrame/10))],&tempRect2,0,NULL,walkingDown.flip_Flag[(int)floor(float(animationFrame/10))]);
				break;
		};
	};

};

void Player::Init(SDL_Renderer *sdlRenderer)
{
	standingLeftRight_SpriteRect = SDL_CreateRect(0,0,16,16);
	standingUp_SpriteRect = SDL_CreateRect(16*5,0,16,16);
	standingDown_SpriteRect = SDL_CreateRect(16*4,0,16,16);

	walkingLeftRight.init(16*0,	0,	SDL_FLIP_NONE,	16*3,	0,	SDL_FLIP_NONE);
	walkingUp.init(		16*2,	0,	SDL_FLIP_NONE,	16*5,	0,	SDL_FLIP_NONE,	16*2,	0,	SDL_FLIP_HORIZONTAL,	16*5,	0,	SDL_FLIP_NONE);
	walkingDown.init(	16*1,	0,	SDL_FLIP_NONE,	16*4,	0,	SDL_FLIP_NONE,	16*1,	0,	SDL_FLIP_HORIZONTAL,	16*4,	0,	SDL_FLIP_NONE);

	animationFrame = 0;	
	animationFrame2 = 0;
	direction = DOWN;
	m_x = 6;
	m_y = 6;
	m_moving = false;
	spritesheet = IMG_LoadTexture(sdlRenderer, "player.png");
	return;
};

bool Player::CheckCollision(int (&levelCollisionArray)[18][20], int x_pos, int y_pos)
{
	if(levelCollisionArray[y_pos][x_pos] == -1)
	{
		return false;
	}
	else
	{
		return true;		
	};
};