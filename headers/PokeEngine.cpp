#include "PokeEngine.h"

void PokeEngine::ApplyDamage(Pokemon* _subject, short int _amount)
{
	if(_amount < 0)
	{
		printf("Battle::ApplyDamage - negative value supplied, use ApplyHealth() instead?\n");
	};
	
	std::cout << _amount << std::endl;

	_subject->CurrHP -= _amount;
	return;
};

void PokeEngine::LevelUpBy(Pokemon* _subject, short int _amount)
{
	if(_amount <= 0)
	{
		printf("Battle::LevelUp - negative value supplied!");
		return;
	};
	_subject->Level += _amount;

	_subject->MaxHP = PokeMath::CalculateStat(PokeMath::MAXHP, POKEDEX_REFERENCE[_subject->Index].BaseHP, _subject->Level);
	_subject->Attack = PokeMath::CalculateStat(PokeMath::ATTACK, POKEDEX_REFERENCE[_subject->Index].BaseAttack, _subject->Level);
	_subject->Defence = PokeMath::CalculateStat(PokeMath::DEFENCE, POKEDEX_REFERENCE[_subject->Index].BaseDefense, _subject->Level);
	_subject->Speed = PokeMath::CalculateStat(PokeMath::SPEED, POKEDEX_REFERENCE[_subject->Index].BaseSpeed, _subject->Level);
	_subject->Special = PokeMath::CalculateStat(PokeMath::SPECIAL, POKEDEX_REFERENCE[_subject->Index].BaseSpecial, _subject->Level);

	return;
};

//
//void PokeEngine::L_ApplyDamage(lua_State*)
//{
//	if(_amount < 1)
//	{
//		printf("Battle::ApplyDamage - negative or null value supplied, use ApplyHealth() instead?\n");
//	};
//	_subject->CurrHP -= _amount;
//	return;
//};