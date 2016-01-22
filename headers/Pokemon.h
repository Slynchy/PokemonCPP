#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include <vector>
#include <iostream>
#include "Moves.h"

#ifndef POKEMON_H
#define POKEMON_H
/*

Character				1	-128			127
Unsigned Char			1	0				255
Signed Char				1	-128			127
Integer					4	-2,147,483,648	2,147,483,647
Signed Int				4	0				4,294,967,295
Unsigned Int			4	-2,147,483,648	2,147,483,647
Short Int				2	-32,768			32,767
Signed short Int		2	0				65,535
Unsigned Short Int		2	-32,768			32,767
Long Int				4	-2,147,483,648	2,147,483,647
Signed Long Int			8	0				4,294,967,295
Unsigned Long Int		8	-2,147,483,648	2,147,483,647
Float					4	1.8E-38			3.4E+38
Double					8	2.2E-308		1.8E+308
Long Double				8	2.2E-308		1.8E+308
Bool					1	True/False		True/False
Wchar_t				2 or 4	0				65,535
*/
#pragma pack(1)

const std::string pokemon_names[151] = 
{
	"BULBASAUR"
};

enum POKEMON_IDS
{
	BULBASAUR
};

const std::string pokemon_filenames[151] = 
{
	"bulbasaur.png"
};

struct LoadedPokeSprites
{
	std::vector<SDL_Texture*> POKEMON_FRONT_SPRITES;
	std::vector<SDL_Texture*> POKEMON_BACK_SPRITES;
};


/* 
	Pokemon in Gen 1 were defined via a structure
	44 bytes in length.

	This is 45 bytes due to OrigTrainerID being 4
	bytes instead of 3. 
*/
struct Pokemon
{
	unsigned char Index;
	short int CurrHP;
	unsigned char LevelPC; // UNUSED?
	unsigned char StatusCond;
	unsigned char Type1;
	unsigned char Type2;
	unsigned char CatchRate_HeldItem;
	unsigned char Move1_index;
	unsigned char Move2_index;
	unsigned char Move3_index;
	unsigned char Move4_index;
	signed short int OrigTrainerID; //4 bytes instead of 3...
	signed int ExperiencePoints;
	signed short int HP_EV;
	signed short int ATTACK_EV;
	signed short int DEFENCE_EV;
	signed short int SPEED_EV;
	signed short int SPECIAL_EV;
	signed short int IVdata;
	unsigned char Move1_PP;
	unsigned char Move2_PP;
	unsigned char Move3_PP;
	unsigned char Move4_PP;
	unsigned char Level;
	short int MaxHP;
	signed short int Attack;
	signed short int Defence;
	signed short int Speed;
	signed short int Special;
};

struct PokedexPokemon
{
	/* Begin "faithful" data: */
	unsigned char DexNum;
	unsigned char BaseHP;
	unsigned char BaseAttack;
	unsigned char BaseDefense;
	unsigned char BaseSpeed;
	unsigned char BaseSpecial;
	unsigned char Type1;
	unsigned char Type2;
	unsigned char CatchRate;
	unsigned char BaseExpYield;
	unsigned char FontSpriteDimensions; //UNUSED
	SDL_Texture *FrontSprite;
	SDL_Texture *BackSprite;
	unsigned char Move1;
	unsigned char Move2;
	unsigned char Move3;
	unsigned char Move4;
	unsigned char GrowthRate;
	unsigned char TMHMFlag_1;
	unsigned char TMHMFlag_2;
	unsigned char TMHMFlag_3;
	unsigned char TMHMFlag_4;
	unsigned char TMHMFlag_5;
	unsigned char TMHMFlag_6;
	unsigned char TMHMFlag_7;
	/* End "faithful" data: */
};

void InitPokemon(Pokemon *pokemon);

const PokedexPokemon POKEDEX_REFERENCE[151] = 
{
	{ 
		BULBASAUR,				// id
		45,						// basehp
		49,						
		49, 
		45, 
		65, 
		GRASS, 
		POISON, 
		45, 
		64, 
		0, 
		0, 
		0,
		TACKLE, 
		GROWL,
		0, 
		0, 
		3, 
		0,
		0,
		0,
		0,
		0,
		0,
		0
	}
};

Pokemon CreatePokemon(
	unsigned char Index,
	short int CurrHP,
	unsigned char LevelPC,
	unsigned char StatusCond,
	unsigned char Type1,
	unsigned char Type2,
	unsigned char CatchRate_HeldItem,
	unsigned char Move1_index,
	unsigned char Move2_index,
	unsigned char Move3_index,
	unsigned char Move4_index,
	signed short int OrigTrainerID,
	signed int ExperiencePoints,
	signed short int HP_EV,
	signed short int ATTACK_EV,
	signed short int DEFENCE_EV,
	signed short int SPEED_EV,
	signed short int SPECIAL_EV,
	signed short int IVdata,
	unsigned char Move1_PP,
	unsigned char Move2_PP,
	unsigned char Move3_PP,
	unsigned char Move4_PP,
	unsigned char Level,
	short int MaxHP,
	signed short int Attack,
	signed short int Defence,
	signed short int Speed,
	signed short int Special);

Pokemon CreatePokemon(
	unsigned char Index);

int LoadPokemonFrontSprites(SDL_Renderer*, LoadedPokeSprites*);
int LoadPokemonBackSprites(SDL_Renderer*, LoadedPokeSprites*);

#endif