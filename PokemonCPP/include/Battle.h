#ifndef BATTLE_H
#define BATTLE_H

#include "SDL.h" // Main SDL library
#include <SDL_mixer.h> 
#include <cstring> 
#include "PokeMath.h"
#include "Player.h"
#include "Pokemon.h"
#include "PokeEngine.h"
#include <chrono>
#include "Localizer.h"

void ShutdownBattle(void);

enum GameStates
{
	MAIN_MENU,
	INGAME,
	GAME_WON,
	GAME_LOST
};

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
		short int playerAccuracy;   //   % of 100
		short int opponentAccuracy; //   ^^^
		short int playerEvasion;    //   ^^^
		short int opponentEvasion;  //   ^^^
		Pokemon pokemon; // an instance
		signed char SelectedMenuItem;
		signed char SelectedAttack;
		Menus CurrentMenu;
		signed char MenuDepth;
		bool missedMove;
		bool oppMissedMove;

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
			Battle::playerEvasion = 100;
			Battle::opponentEvasion = 100;
			Battle::playerAccuracy = 100;
			Battle::opponentAccuracy = 100;
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
			Battle::playerEvasion = 100;
			Battle::opponentEvasion = 100;
			Battle::playerAccuracy = 100;
			Battle::opponentAccuracy = 100;
		};

		void Reset();

		void UpdateUIPosition(Keys*);
		void Logic(Keys*, Player*, bool*, SDL_Renderer*, GameStates*);
		void Battle::ResetUI();
		short int Battle::GetPlayerHP();
		short int Battle::GetOpponentHP();
		Pokemon Battle::GetActivePokemon();
		bool Battle::HasActivePokemonFainted();
		bool Battle::HasOpponentActivePokemonFainted();
		void Battle::RunAway(Player*);
		void Battle::Shutdown(Player*);
		void Battle::SwitchActivePokemon(short int, Player*);

		// Returns the modifier for types against eachother in a lookup table
		float Battle::CheckTypeMatch(TYPES _movetype, TYPES _opponentType);

		// Turns PokemonC++ Type array into the correct type for the lookup table
		TYPES Battle::TranslateTypeIntoLookup(TYPES _type);

		void Battle::ExecuteMoveEffect(Pokemon*, Pokemon*,  Move _move, int _damage);

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

		static short int Battle::CalculateAccuracy(short int _moveAcc, short int _userAcc, short int _defenderEvasion);


	//	void CreateBattle(PokeParty*,Trainer*);
};
int StatusConditionUpdate(Pokemon* _pokemon, Battle* _battle);

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
	SDL_Texture* victory_screen;
	SDL_Texture* failure_screen;
	int Load(SDL_Renderer* );
	void Shutdown();
};

#endif