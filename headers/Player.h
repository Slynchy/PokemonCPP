#include "SDL.h" // Main SDL library
#include <SDL_image.h> // SDL Image library
#include "../src/SDLFunctions.h"
#include "Zones.h"
#include "Text.h"
#include "Pokemon.h"
#include <math.h>
#include <vector>
#include <iostream>

#ifndef PLAYER_H
#define PLAYER_H

enum directions { RIGHT , LEFT , UP , DOWN };

struct Animation
{
	std::vector<SDL_Rect> frames;
	std::vector<SDL_RendererFlip> flip_Flag;
	void init(int f1_x, int f1_y, SDL_RendererFlip f1_flip,int f2_x, int f2_y, SDL_RendererFlip f2_flip);
	void init(int f1_x, int f1_y, SDL_RendererFlip f1_flip,int f2_x, int f2_y, SDL_RendererFlip f2_flip, int f3_x, int f3_y, SDL_RendererFlip f3_flip);
	void init(int f1_x, int f1_y, SDL_RendererFlip f1_flip,int f2_x, int f2_y, SDL_RendererFlip f2_flip, int f3_x, int f3_y, SDL_RendererFlip f3_flip, int f4_x, int f4_y, SDL_RendererFlip f4_flip);
};

struct PokeParty
{
	unsigned char Num_of_Pokemon;
	unsigned char Poke1_index;
	unsigned char Poke2_index;
	unsigned char Poke3_index;
	unsigned char Poke4_index;
	unsigned char Poke5_index;
	unsigned char Poke6_index;
	std::vector<Pokemon> Party;
	void InsertPokemon(Pokemon* _pokemon)
	{
		Party.push_back(*_pokemon);	
		return;
	};
	PokeParty()
	{
		//blanky-wanky-woo
	};
	PokeParty(Pokemon* _pokemon,Pokemon* _pokemon2)
	{
		//blanky-wanky-woo
		Party.push_back(*_pokemon);	
		Party.push_back(*_pokemon2);	
	};
};

void InitPokeParty(PokeParty *party);

class Trainer
{
	private:
		std::string m_Name;
		PokeParty m_party;
		int m_ActivePokemon;

	public:
		int GetActivePokemon()
		{
			return m_ActivePokemon;
		};
		void SetActivePokemon(int _input)
		{
			m_ActivePokemon = _input;
			return;
		};
		PokeParty* GetParty()
		{
			return &m_party;
		};
};

class Player: public Trainer
{
	private:
		bool InBattle;
		bool m_willBattle;

	public:
		int m_x;
		int m_y;
		SDL_Texture *spritesheet;
		bool m_moving;
		directions direction;
		SDL_Rect standingLeftRight_SpriteRect;
		SDL_Rect standingUp_SpriteRect;
		SDL_Rect standingDown_SpriteRect;
		unsigned char animationFrame;
		unsigned char animationFrame2;
		int zoneIndex;
		bool CanMove;
		bool beatTrainer1;
		bool beatTrainer2;
		bool beatTrainer3;
		short int currentOpponentID;

		Animation walkingLeftRight;
		Animation walkingUp;
		Animation walkingDown;

		void KeyboardInput(Keys *keys, std::vector<Zone>& levelCollisionArray);
		void Draw(SDL_Renderer *sdlRenderer);
		bool CheckCollision(std::vector<Zone> levelCollisionArray, int x_pos, int y_pos);

		void SetInBattle(bool _param)
		{
			InBattle = _param;
		};
		bool GetInBattle()
		{
			return InBattle;
		};

		void SetIsBattleScheduled(bool _param)
		{
			m_willBattle = _param;
			return;
		};
		bool IsBattleScheduled()
		{
			return m_willBattle;
		};

		Player(SDL_Renderer *sdlRenderer)
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
			zoneIndex = 0; // palletTown = 0, route 1 = 1, etc.
			m_x = 6;
			m_y = 6;
			m_moving = false;
			spritesheet = IMG_LoadTexture(sdlRenderer, "player.png");
			InBattle = false;
			CanMove = true;
			this->SetActivePokemon(0);

			SetInBattle(false);
			m_willBattle = false;
			beatTrainer1 = false;
			beatTrainer2 = false;
			beatTrainer3 = false;
			currentOpponentID = 0;

			InitPokeParty(this->GetParty());
		};

		static int GetObjectAtPosition(std::vector<Zone> levelCollisionArray, int x_pos, int y_pos);
};

#endif