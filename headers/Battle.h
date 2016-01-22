#include "SDL.h" // Main SDL library
//#include <SDL_image.h> // SDL Image library
#include "PokeMath.h"
#include "Player.h"
#include "Trainer.h"
#include "Pokemon.h"

#ifndef BATTLE_H
#define BATTLE_H

enum PossibleActions
{
	UNDECIDED,
	ATTACK,
	ITEM,
	RUN
};

class Battle
{
	public:
		PokeParty *PlayerParty;
		PokeParty OpponentParty;
		Trainer *OpponentTrainer;
		bool PlayersTurn;
		PossibleActions ChosenAction;
		Pokemon *pokemon;
		signed char SelectedMenuItem;
		signed char SelectedAttack;
		signed char CurrentMenu;
		void CreateBattle(PokeParty*,Pokemon*);
		void UpdateUIPosition(Keys*);
		void Logic(Keys*, Player*);
		void Battle::ResetUI();
	//	void CreateBattle(PokeParty*,Trainer*);
};

struct BattleScreen
{
	SDL_Texture* OpponentInfo;
	SDL_Texture* PlayerInfo;
	SDL_Texture* Frame;
	SDL_Texture* Frame_Fight;
	SDL_Texture* HPBar;
	SDL_Texture* arrow;
	int Load(SDL_Renderer* );
};


















#endif