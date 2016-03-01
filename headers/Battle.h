#include "SDL.h" // Main SDL library
#include <SDL_mixer.h> 
#include <cstring> 
#include "PokeMath.h"
#include "Player.h"
#include "Pokemon.h"
#include "PokeEngine.h"
#include <chrono>

#ifndef BATTLE_H
#define BATTLE_H

void ShutdownBattle(void);

class Battle
{
	private:
		static Battle* currentBattle;
		Pokemon PlayersActivePokemon; // an instance 
		bool isTrainer;
		unsigned char opponentActivePkmn;
		Player* currentPlayer;
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

		Battle(Player* _Player, PokeParty* _oppParty)
		{
			Battle::PlayerParty = _Player->GetParty();
			Battle::PlayersActivePokemon = Battle::PlayerParty->Party[0];
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
		Battle(Player* _Player, Pokemon _OpponentPokemon)
		{
			Battle::PlayerParty = _Player->GetParty();
			Battle::PlayersActivePokemon = Battle::PlayerParty->Party[0];
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
		void Logic(Keys*, Player*, bool*);
		void Battle::ResetUI();
		short int Battle::GetPlayerHP();
		short int Battle::GetOpponentHP();
		Pokemon Battle::GetActivePokemon();
		bool Battle::HasActivePokemonFainted();
		bool Battle::HasOpponentActivePokemonFainted();
		void Battle::RunAway(Player*);
		void Battle::Shutdown(Player*);
		void Battle::SwitchActivePokemon(short int, Player*);

		void Battle::ExecuteMoveEffect(Pokemon*, Pokemon*, MOVE_EFFECTS, int _damage);

		static Battle* GetCurrentBattle()
		{
			return currentBattle;
		};
		static void SetCurrentBattle(Battle* _newBattle)
		{
			currentBattle = _newBattle;
			return; 
		};

		inline Player* GetPlayer(void)
		{
			return currentPlayer;
		};

		inline void Battle::ExternShutdown()
		{
			this->Shutdown(this->GetPlayer());
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
	SDL_Texture* HPBar_Outline;
	SDL_Texture* arrow;
	SDL_Texture* pkmnSelectScreen;
	SDL_Texture* lvlslash;
	SDL_Texture* pkmn_icon;
	SDL_Texture* pokedex;
	SDL_Texture* pokedexdetails;
	SDL_Texture* itemsMenu;
	SDL_Texture* pkmnselection_box;
	int Load(SDL_Renderer* );
	void Shutdown();
};

#endif