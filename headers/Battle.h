#include "SDL.h" // Main SDL library
//#include <SDL_image.h> // SDL Image library
#include "PokeMath.h"
#include "Player.h"
#include "Pokemon.h"
#include "PokeEngine.h"

#ifndef BATTLE_H
#define BATTLE_H

class Battle
{
	private:
		static Battle* currentBattle;
		Pokemon PlayersActivePokemon; // an instance 
		bool isTrainer;
		unsigned char opponentActivePkmn;
	public:
		enum Menus
		{
			UNDECIDED,
			FIGHT,
			PKMN,
			ITEMS,
			RUN, 
			VICTORY
		};
		PokeParty *PlayerParty;
		PokeParty *OpponentParty;
		Trainer *OpponentTrainer;
		bool PlayersTurn;
		//PossibleActions ChosenAction;
		Pokemon pokemon; // an instance
		signed char SelectedMenuItem;
		signed char SelectedAttack;
		Menus CurrentMenu;
		signed char MenuDepth;

		Battle(PokeParty* _PlayerParty, PokeParty* _oppParty)
		{
			Battle::PlayerParty = _PlayerParty;
			Battle::PlayersActivePokemon = _PlayerParty->Party[0];
			Battle::OpponentParty = _oppParty;
			Battle::pokemon = _oppParty->Party[0];
			Battle::SelectedMenuItem = 0;
			Battle::CurrentMenu = UNDECIDED;
			Battle::MenuDepth = 0;
			Battle::SelectedAttack = 0;
			Battle::PlayersTurn = true;
			Battle::isTrainer = true;
			Battle::opponentActivePkmn = 0;
		};
		Battle(PokeParty* _PlayerParty, Pokemon _OpponentPokemon)
		{
			Battle::PlayerParty = _PlayerParty;
			Battle::PlayersActivePokemon = _PlayerParty->Party[0];
			Battle::pokemon = _OpponentPokemon;
			Battle::SelectedMenuItem = 0;
			Battle::CurrentMenu = UNDECIDED;
			Battle::MenuDepth = 0;
			Battle::SelectedAttack = 0;
			Battle::PlayersTurn = true;
			Battle::isTrainer = false;
		};

		void Reset();

		void UpdateUIPosition(Keys*);
		void Logic(Keys*, Player*);
		void Battle::ResetUI();
		short int Battle::GetPlayerHP();
		short int Battle::GetOpponentHP();
		Pokemon Battle::GetActivePokemon();
		bool Battle::HasActivePokemonFainted();
		bool Battle::HasOpponentActivePokemonFainted();
		void Battle::RunAway(Player*);
		void Battle::Shutdown(Player*);

		void Battle::ExecuteMoveEffect(Pokemon*, Pokemon*, MOVE_EFFECTS);

		static Battle* GetCurrentBattle()
		{
			return currentBattle;
		};
		static void SetCurrentBattle(Battle* _newBattle)
		{
			currentBattle = _newBattle;
			return; 
		};


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
	void Shutdown();
};


















#endif