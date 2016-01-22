#include "PokeMath.h"

int CalculateDamage(int _attacker_level, int _attacker_attack, int _defender_defense, int _base_damage, int _modifier)
{
	float part1 = (float)((float)(2*((float)_attacker_level)+10)/250);
	float part2 = (float)(((float)_attacker_attack)/((float)_defender_defense));
	float part3 = (float)_base_damage;
	float part4 = 2.0f;
	float part1to4complete = part1 * part2 * part3 + part4;
	int complete = part1to4complete * _modifier;
	return complete;
};