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