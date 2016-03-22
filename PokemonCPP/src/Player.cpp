#include "Player.h"

void InitPokeParty(PokeParty *party)
{
	party->Num_of_Pokemon = 0;
	for( size_t i = 0; i < party->Party.size(); i++)
	{
		InitPokemon(&party->Party[i]);
	};
};

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

void Player::KeyboardInput(Keys *keys, std::vector<Zone>& levelCollisionArray)
{
	if(!Player::m_moving && CanMove == true){
		if(keys->W)
		{
			direction = UP;
			Player::m_moving = true;
			if(Player::CheckCollision(levelCollisionArray,Player::m_x,Player::m_y-1) == false)
			{
				Player::m_y -= 1;
			};
		} else if(keys->S)
		{
			direction = DOWN;
			Player::m_moving = true;
			if(Player::CheckCollision(levelCollisionArray,Player::m_x,Player::m_y+1) == false)
			{
				Player::m_y += 1;
			};
		} else if(keys->A)
		{
			direction = LEFT;
			Player::m_moving = true;
			if(Player::CheckCollision(levelCollisionArray,Player::m_x-1,Player::m_y) == false)
			{
				Player::m_x -= 1;
			};
		} else if(keys->D)
		{
			direction = RIGHT;
			Player::m_moving = true;
			if(Player::CheckCollision(levelCollisionArray,Player::m_x+1,Player::m_y) == false)
			{
				Player::m_x += 1;
			};
		};
	};
	if(keys->ENTER && !this->activeMessage->Active)
	{
		switch(direction)
		{
		case UP:
			if(GetObjectAtPosition(levelCollisionArray,Player::m_x, Player::m_y-1) == 5)
			{
				if(beatTrainer1  == false)
				{
					this->activeMessage = new Message(Language_Master::StringToCString(Language_Master::LORELEI_TEXT));
					currentOpponentID = 1;
				};
			};
			if(GetObjectAtPosition(levelCollisionArray,Player::m_x, Player::m_y-1) == 6)
			{
				if(beatTrainer2  == false)
				{
					this->activeMessage = new Message(Language_Master::StringToCString(Language_Master::BRUNO_TEXT));
					currentOpponentID = 2;
				};
			};
			if(GetObjectAtPosition(levelCollisionArray,Player::m_x, Player::m_y-1) == 7)
			{
				if(beatTrainer3  == false)
				{
					currentOpponentID = 3;
					this->activeMessage = new Message(Language_Master::StringToCString(Language_Master::AGATHA_TEXT));
				};
			};
			break;
		case DOWN:
			if(GetObjectAtPosition(levelCollisionArray,Player::m_x, Player::m_y+1) == 5)
			{
				if(beatTrainer1  == false)
				{
					this->activeMessage = new Message(Language_Master::StringToCString(Language_Master::LORELEI_TEXT));
					currentOpponentID = 1;
				};
			};
			if(GetObjectAtPosition(levelCollisionArray,Player::m_x, Player::m_y+1) == 6)
			{
				if(beatTrainer2  == false)
				{
					this->activeMessage = new Message(Language_Master::StringToCString(Language_Master::BRUNO_TEXT));
					currentOpponentID = 2;
				};
			};
			if(GetObjectAtPosition(levelCollisionArray,Player::m_x, Player::m_y+1) == 7)
			{
				if(beatTrainer3  == false)
				{
					this->activeMessage = new Message(Language_Master::StringToCString(Language_Master::AGATHA_TEXT));
					currentOpponentID = 3;
				};
			};
			break;
		case RIGHT:
			if(GetObjectAtPosition(levelCollisionArray,Player::m_x+1, Player::m_y) == 5)
			{
				if(beatTrainer1  == false)
				{
					this->activeMessage = new Message(Language_Master::StringToCString(Language_Master::LORELEI_TEXT));
					currentOpponentID = 1;
				};
			};
			if(GetObjectAtPosition(levelCollisionArray,Player::m_x+1, Player::m_y) == 6)
			{
				if(beatTrainer2  == false)
				{
					this->activeMessage = new Message(Language_Master::StringToCString(Language_Master::BRUNO_TEXT));
					currentOpponentID = 2;
				};
			};
			if(GetObjectAtPosition(levelCollisionArray,Player::m_x+1, Player::m_y) == 7)
			{
				if(beatTrainer3  == false)
				{
					this->activeMessage = new Message(Language_Master::StringToCString(Language_Master::AGATHA_TEXT));
					currentOpponentID = 3;
				};
			};
			break;
		case LEFT:
			if(GetObjectAtPosition(levelCollisionArray,Player::m_x-1, Player::m_y) == 5)
			{
				if(beatTrainer1  == false)
				{
					this->activeMessage = new Message(Language_Master::StringToCString(Language_Master::LORELEI_TEXT));
					currentOpponentID = 1;
				};
			};
			if(GetObjectAtPosition(levelCollisionArray,Player::m_x-1, Player::m_y) == 6)
			{
				if(beatTrainer2 == false)
				{
					this->activeMessage = new Message(Language_Master::StringToCString(Language_Master::BRUNO_TEXT));
					currentOpponentID = 2;
				};
			};
			if(GetObjectAtPosition(levelCollisionArray,Player::m_x-1, Player::m_y) == 7)
			{
				if(beatTrainer3  == false)
				{
					this->activeMessage = new Message(Language_Master::StringToCString(Language_Master::AGATHA_TEXT));
					currentOpponentID = 3;
				};
			};
			break;
		default:
			break;
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

bool Player::CheckCollision(std::vector<Zone> levelCollisionArray, int x_pos, int y_pos)
{
	if(Player::zoneIndex == -1 || size_t(Player::zoneIndex) > levelCollisionArray.size()) return false;
	if(x_pos > (unsigned char)levelCollisionArray[Player::zoneIndex].objectData[0].size() || 
		y_pos > (unsigned char)(levelCollisionArray[Player::zoneIndex].objectData.size()-1) ||
		x_pos < 0 ||
		y_pos < 0)
	{
		if(CheckZone(levelCollisionArray, x_pos, y_pos-1) != -1 && CheckZone(levelCollisionArray, x_pos, y_pos-1) != Player::zoneIndex)
		{
			return false;
		};
	};

	int zonePos_X = (x_pos - levelCollisionArray[Player::zoneIndex].world_x );
	int zonePos_Y = (y_pos - levelCollisionArray[Player::zoneIndex].world_y );
	if(zonePos_X < 0 || zonePos_Y < 0 || zonePos_X > levelCollisionArray[Player::zoneIndex].x_size || zonePos_Y > levelCollisionArray[Player::zoneIndex].y_size-1)
	{
		return false;
	};
	if(levelCollisionArray[Player::zoneIndex].objectData[zonePos_Y][zonePos_X] == -1)
	{
		return false;
	}
	else
	{
		return true;		
	};
};

int Player::GetObjectAtPosition(std::vector<Zone> levelCollisionArray, int x_pos, int y_pos)
{
	return levelCollisionArray[0].objectData[y_pos][x_pos];
};