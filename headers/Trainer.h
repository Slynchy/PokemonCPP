#include <string>
#include "Player.h"

#ifndef TRAINER_H
#define TRAINER_H

struct Trainer
{
	std::string Name;
	PokeParty Party;
};
/*
Name	2-8 bytes
Name string	1-7 bytes
Terminator	1 byte
Custom move marker	1 byte
Pokémon	2-6 bytes
Level	1 byte
Species	1 byte
Moveset	4 bytes
Terminator	1 byte
*/

#endif