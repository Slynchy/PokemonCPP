#include "PokeMath.h"

int PokeMath::CalculateDamage(int _attacker_level, int _attacker_attack, int _defender_defense, int _base_damage, int _modifier)
{
	
	float complete = ( ((float)(2*_attacker_level+10)/250) * (float)(_attacker_attack/_defender_defense) * _base_damage + 2 ) * 1.0f;

	std::cout << "CalcDamg: " << complete << std::endl;

	return (int)complete;
};

double PokeMath::LinearInterpolate(double y1,double y2,double mu)
{
	return(y1*(1-mu)+y2*mu);
};

int PokeMath::CalculateStat(Stats _STAT, int _BaseStat, int _Level)
{
	int stat;
	switch(_STAT)
	{
		case ATTACK:
			stat = floor(((_BaseStat + 0) * 2 + 63) * _Level / 100) + 5;
			break;
		case DEFENCE:
			stat = floor(((_BaseStat + 0) * 2 + 63) * _Level / 100) + 5;
			break;
		case SPEED:
			stat = floor(((_BaseStat + 0) * 2 + 63) * _Level / 100) + 5;
			break;
		case SPECIAL:
			stat = floor(((_BaseStat + 0) * 2 + 63) * _Level / 100) + 5;
			break;
		case MAXHP:
			stat = floor(((_BaseStat + 0) * 2 + 63) * _Level / 100) + _Level + 10;
			break;
	};
	return stat;
};