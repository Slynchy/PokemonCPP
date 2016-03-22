#include "PokeMath.h"

int PokeMath::CalculateDamage(int _attacker_level, int _attacker_attack, int _defender_defense, int _base_damage, int _modifier)
{
	// The random number is between 85 and 100
	// So rand()%15+1 = a number between 1 and 15
	// then +85 to offset it
	int randomNumber = ((rand()%15)+1);
	randomNumber += 85;

	//Damage Formula = (((((((Level × 2 ÷ 5) + 2) × BasePower × [Sp]Atk ÷ 50) ÷ [Sp]Def) × Mod1) + 2) × CH × Mod2 × R ÷ 100) × STAB × Type1 × Type2 × Mod3)
	float form = ((((((((_attacker_level * 2 / 5) + 2) * _base_damage * _attacker_attack / 50) / _defender_defense) * 1) + 2) * 1 * 1 * randomNumber / 100) * 1 * 1 * 1 * 1);


	//float complete = ((((2 * _attacker_level / 5 + 2) * _attacker_attack * _base_damage / _defender_defense) / 50) + 2) * 1 * 1 * 100 / 100;

	std::cout << "CalcDamg: " << form << std::endl;

	return (int)form;
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
			stat = int(floor(((_BaseStat + 0) * 2 + 63) * _Level / 100) + 5);
			break;
		case DEFENCE:
			stat = int(floor(((_BaseStat + 0) * 2 + 63) * _Level / 100) + 5);
			break;
		case SPEED:
			stat = int(floor(((_BaseStat + 0) * 2 + 63) * _Level / 100) + 5);
			break;
		case SPECIAL:
			stat = int(floor(((_BaseStat + 0) * 2 + 63) * _Level / 100) + 5);
			break;
		case MAXHP:
			stat = int(floor(((_BaseStat + 0) * 2 + 63) * _Level / 100) + _Level + 10);
			break;
	};
	return stat;
};