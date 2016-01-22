#include "Pokemon.h"

void InitPokemon(Pokemon *pokemon)
{
	pokemon->Index = 0;
	pokemon->CurrHP = 0;
	pokemon->LevelPC = 0;
	pokemon->StatusCond = 0;
	pokemon->Type1 = 0;
	pokemon->Type2 = 0;
	pokemon->CatchRate_HeldItem = 0;
	pokemon->Move1_index = 0;
	pokemon->Move2_index = 0;
	pokemon->Move3_index = 0;
	pokemon->Move4_index = 0;
	pokemon->OrigTrainerID = 0;
	pokemon->ExperiencePoints = 0;
	pokemon->HP_EV = 0;
	pokemon->ATTACK_EV = 0;
	pokemon->DEFENCE_EV = 0;
	pokemon->SPEED_EV = 0;
	pokemon->SPECIAL_EV = 0;
	pokemon->IVdata = 0;
	pokemon->Move1_PP = 0;
	pokemon->Move2_PP = 0;
	pokemon->Move3_PP = 0;
	pokemon->Move4_PP = 0;
	pokemon->Level = 0;
	pokemon->MaxHP = 0;
	pokemon->Attack = 0;
	pokemon->Defence = 0;
	pokemon->Speed = 0;
	pokemon->Special = 0;
	return;
};

Pokemon CreatePokemon(unsigned char Index)
{
	Pokemon pokemon;
	pokemon.Index = Index; 
	pokemon.CurrHP = POKEDEX_REFERENCE[0].BaseHP;
	pokemon.LevelPC = 1;
	pokemon.StatusCond = 0;
	pokemon.Type1 = POKEDEX_REFERENCE[0].Type1;
	pokemon.Type2 = POKEDEX_REFERENCE[0].Type2;
	pokemon.CatchRate_HeldItem = POKEDEX_REFERENCE[0].CatchRate;
	pokemon.Move1_index = POKEDEX_REFERENCE[0].Move1;
	pokemon.Move2_index = POKEDEX_REFERENCE[0].Move2;
	pokemon.Move3_index = 0;
	pokemon.Move4_index = 0;
	pokemon.OrigTrainerID = 0;
	pokemon.ExperiencePoints = 0;
	pokemon.HP_EV = 0;
	pokemon.ATTACK_EV = 0;
	pokemon.DEFENCE_EV = 0;
	pokemon.SPEED_EV = 0;
	pokemon.SPECIAL_EV = 0;
	pokemon.IVdata = 0;
	pokemon.Move1_PP = 0;
	pokemon.Move2_PP = 0;
	pokemon.Move3_PP = 0;
	pokemon.Move4_PP = 0;
	pokemon.Level = 1;
	pokemon.MaxHP = POKEDEX_REFERENCE[0].BaseHP;
	pokemon.Attack = POKEDEX_REFERENCE[0].BaseAttack;
	pokemon.Defence = POKEDEX_REFERENCE[0].BaseDefense;
	pokemon.Speed = POKEDEX_REFERENCE[0].BaseSpeed;
	pokemon.Special = POKEDEX_REFERENCE[0].BaseSpecial;
	return pokemon;
};

int LoadPokemonFrontSprites(SDL_Renderer* sdlRenderer, LoadedPokeSprites* _loadedsprites)
{
	for( int i = 0; i < 151; ++i)
	{
		if(!POKEDEX_REFERENCE->DexNum && i != 0)
			break;
		std::string s = pokemon_filenames[i];
		s = s.insert (0, "frontsprites/");
		_loadedsprites->POKEMON_FRONT_SPRITES.push_back(IMG_LoadTexture(sdlRenderer, s.c_str()));
		if(!_loadedsprites->POKEMON_FRONT_SPRITES[i])
			return -1;
	};
	return 0;
};

int LoadPokemonBackSprites(SDL_Renderer* sdlRenderer, LoadedPokeSprites* _loadedsprites)
{
	for( int i = 0; i < 151; ++i)
	{
		if(!POKEDEX_REFERENCE->DexNum && i != 0)
			break;
		std::string s = pokemon_filenames[i];
		s = s.insert (0, "backsprites/");
		_loadedsprites->POKEMON_BACK_SPRITES.push_back(IMG_LoadTexture(sdlRenderer, s.c_str()));
		if(!_loadedsprites->POKEMON_BACK_SPRITES[i])
			return -1;
	};
	return 0;
};