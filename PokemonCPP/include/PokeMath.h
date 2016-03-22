#include <iostream>

#ifndef POKEMATH_H
#define POKEMATH_H

class PokeMath
{
	public : 
		enum Stats
		{
			ATTACK,
			DEFENCE,
			SPEED,
			SPECIAL,
			MAXHP
		};
		static int CalculateDamage(int _attacker_level, int _attacker_attack, int _defender_defense, int _base_damage, int _modifier);
		static double LinearInterpolate(double y1,double y2,double mu);
		static int CalculateStat(Stats _STAT, int _BaseStat, int _Level);
};

#endif