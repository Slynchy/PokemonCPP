#include "Pokemon.h"

void InitPokemon(Pokemon *pokemon)
{
	pokemon->Index = 0;
	pokemon->CurrHP = 0;
	pokemon->LevelPC = 0;
	pokemon->StatusCond = NONE;
	pokemon->Type1 = 0;
	pokemon->Type2 = 0;
	pokemon->CatchRate_HeldItem = 0;
	pokemon->MoveSet[0].Index = 0;
	pokemon->MoveSet[1].Index = 0;
	pokemon->MoveSet[2].Index = 0;
	pokemon->MoveSet[3].Index = 0;
	pokemon->OrigTrainerID = 0;
	pokemon->ExperiencePoints = 0;
	pokemon->HP_EV = 0;
	pokemon->ATTACK_EV = 0;
	pokemon->DEFENCE_EV = 0;
	pokemon->SPEED_EV = 0;
	pokemon->SPECIAL_EV = 0;
	pokemon->IVdata = 0;
	pokemon->MoveSet[0].PP = 0;
	pokemon->MoveSet[1].PP = 0;
	pokemon->MoveSet[2].PP = 0;
	pokemon->MoveSet[3].PP = 0;
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
	pokemon.Level = 1;
	pokemon.CurrHP = PokeMath::CalculateStat(PokeMath::MAXHP, POKEDEX_REFERENCE[Index].BaseHP, pokemon.Level);
	pokemon.LevelPC = 1;
	pokemon.StatusCond = NONE;
	pokemon.Type1 = POKEDEX_REFERENCE[Index].Type1;
	pokemon.Type2 = POKEDEX_REFERENCE[Index].Type2;
	pokemon.CatchRate_HeldItem = POKEDEX_REFERENCE[0].CatchRate;
	pokemon.MoveSet[0].Index = POKEDEX_REFERENCE[Index].Move1;
	pokemon.MoveSet[1].Index = POKEDEX_REFERENCE[Index].Move2;
	pokemon.MoveSet[2].Index = 0;
	pokemon.MoveSet[3].Index = 0;
	pokemon.OrigTrainerID = 0;
	pokemon.ExperiencePoints = 0;
	pokemon.HP_EV = 0;
	pokemon.ATTACK_EV = 0;
	pokemon.DEFENCE_EV = 0;
	pokemon.SPEED_EV = 0;
	pokemon.SPECIAL_EV = 0;
	pokemon.IVdata = 0;
	pokemon.MoveSet[0].PP = MOVES_ARRAY[pokemon.MoveSet[0].Index].PP;
	pokemon.MoveSet[1].PP = MOVES_ARRAY[pokemon.MoveSet[1].Index].PP;
	pokemon.MoveSet[2].PP = MOVES_ARRAY[pokemon.MoveSet[2].Index].PP;
	pokemon.MoveSet[3].PP = MOVES_ARRAY[pokemon.MoveSet[3].Index].PP;
	pokemon.MaxHP = PokeMath::CalculateStat(PokeMath::MAXHP, POKEDEX_REFERENCE[Index].BaseHP, pokemon.Level);
	pokemon.Attack = PokeMath::CalculateStat(PokeMath::ATTACK, POKEDEX_REFERENCE[Index].BaseAttack, pokemon.Level);
	pokemon.Defence = PokeMath::CalculateStat(PokeMath::DEFENCE, POKEDEX_REFERENCE[Index].BaseDefense, pokemon.Level);
	pokemon.Speed = PokeMath::CalculateStat(PokeMath::SPEED, POKEDEX_REFERENCE[Index].BaseSpeed, pokemon.Level);
	pokemon.Special = PokeMath::CalculateStat(PokeMath::SPECIAL, POKEDEX_REFERENCE[Index].BaseSpecial, pokemon.Level);
	return pokemon;
};

Pokemon CreatePokemon(unsigned char Index,unsigned char _Move1_index,unsigned char _Move2_index,unsigned char _Move3_index,unsigned char _Move4_index)
{
	Pokemon pokemon;
	pokemon.Index = Index; 
	pokemon.LevelPC = 1;
	pokemon.StatusCond = NONE;
	pokemon.Type1 = POKEDEX_REFERENCE[Index].Type1;
	pokemon.Type2 = POKEDEX_REFERENCE[Index].Type2;
	pokemon.CatchRate_HeldItem = POKEDEX_REFERENCE[0].CatchRate;
	pokemon.MoveSet[0].Index = _Move1_index;
	pokemon.MoveSet[1].Index = _Move2_index;
	pokemon.MoveSet[2].Index = _Move3_index;
	pokemon.MoveSet[3].Index = _Move4_index;
	pokemon.OrigTrainerID = 0;
	pokemon.ExperiencePoints = 0;
	pokemon.HP_EV = 0;
	pokemon.ATTACK_EV = 0;
	pokemon.DEFENCE_EV = 0;
	pokemon.SPEED_EV = 0;
	pokemon.SPECIAL_EV = 0;
	pokemon.IVdata = 0;
	pokemon.MoveSet[0].PP = MOVES_ARRAY[pokemon.MoveSet[0].Index].PP;
	pokemon.MoveSet[1].PP = MOVES_ARRAY[pokemon.MoveSet[1].Index].PP;
	pokemon.MoveSet[2].PP = MOVES_ARRAY[pokemon.MoveSet[2].Index].PP;
	pokemon.MoveSet[3].PP = MOVES_ARRAY[pokemon.MoveSet[3].Index].PP;
	pokemon.Level = 1;
	pokemon.CurrHP = POKEDEX_REFERENCE[Index].BaseHP;
	pokemon.MaxHP = POKEDEX_REFERENCE[Index].BaseHP;
	pokemon.Attack = POKEDEX_REFERENCE[Index].BaseAttack;
	pokemon.Defence = POKEDEX_REFERENCE[Index].BaseDefense;
	pokemon.Speed = POKEDEX_REFERENCE[Index].BaseSpeed;
	pokemon.Special = POKEDEX_REFERENCE[Index].BaseSpecial;
	return pokemon;
};

int LoadPokemonFrontSprites(SDL_Renderer* sdlRenderer, LoadedPokeSprites* _loadedsprites)
{
	for( int i = 0; i < 151; ++i)
	{
		std::string tempString = pokemon_names[POKEDEX_REFERENCE[i].DexNum];
		std::transform(tempString.begin(), tempString.end(), tempString.begin(), ::tolower);
		tempString.append(".png");

		//if(!POKEDEX_REFERENCE->DexNum && i != 0)
		//	break;
		tempString = tempString.insert (0, "frontsprites/");
		_loadedsprites->POKEMON_FRONT_SPRITES.push_back(IMG_LoadTexture(sdlRenderer, tempString.c_str()));
		if(!_loadedsprites->POKEMON_FRONT_SPRITES[i])
			//anus
			return -1;
	};
	return 0;
};

int LoadPokemonBackSprites(SDL_Renderer* sdlRenderer, LoadedPokeSprites* _loadedsprites)
{
	for( int i = 0; i < 151; ++i)
	{
		std::string tempString = pokemon_names[POKEDEX_REFERENCE[i].DexNum];
		std::transform(tempString.begin(), tempString.end(), tempString.begin(), ::tolower);
		tempString.append("b.png");

	//	if(!POKEDEX_REFERENCE->DexNum && i != 0)
	//		break;
		tempString = tempString.insert (0, "backsprites/");
		_loadedsprites->POKEMON_BACK_SPRITES.push_back(IMG_LoadTexture(sdlRenderer, tempString.c_str()));
		if(!_loadedsprites->POKEMON_BACK_SPRITES[i])
			//printf(tempString.c_str());
			//anus
			return -1;
	};
	return 0;
};