#include "Battle.h"

void Battle::Reset()
{
	Battle::ResetUI();
	Battle::PlayerParty = NULL;
	Battle::SelectedMenuItem = 0;
	Battle::PlayersTurn = true;
	return;
};

void Battle::ResetUI()
{
	Battle::CurrentMenu = UNDECIDED;
	Battle::MenuDepth = 0;
	Battle::SelectedMenuItem = 0;
	Battle::SelectedAttack = 0;
	return;
};

void Battle::RunAway(Player* _player)
{
	Battle::Shutdown(_player);
	return;
};

void Battle::Shutdown(Player* _player)
{
	//_player->GetParty()->Party[0] = Battle::PlayersActivePokemon;
	_player->GetParty()->Party[0].StatusCond = Battle::PlayersActivePokemon.StatusCond;
	_player->GetParty()->Party[0].CurrHP = Battle::PlayersActivePokemon.CurrHP;
	_player->GetParty()->Party[0].MoveSet[0].PP = Battle::PlayersActivePokemon.MoveSet[0].PP;
	_player->GetParty()->Party[0].MoveSet[1].PP = Battle::PlayersActivePokemon.MoveSet[1].PP;
	_player->GetParty()->Party[0].MoveSet[2].PP = Battle::PlayersActivePokemon.MoveSet[2].PP;
	_player->GetParty()->Party[0].MoveSet[3].PP = Battle::PlayersActivePokemon.MoveSet[3].PP;

	_player->SetInBattle(false);
	delete this;
	return;
};

void Battle::Logic(Keys* _keys, Player* _player)
{
	if(HasOpponentActivePokemonFainted() == true)
	{
		CurrentMenu = VICTORY;
	} 
	else if(HasActivePokemonFainted() == true)
	{
		// fail
	};

	if(CurrentMenu == VICTORY)
	{
		if(_keys->ENTER == false)
		{
			// naffink
			return;
		}
		else
		{
			if(Battle::isTrainer && opponentActivePkmn < (OpponentParty->Party.size()-1))
			{
				Battle::pokemon = OpponentParty->Party[++opponentActivePkmn];
				Battle::PlayersTurn = true;
				Battle::ResetUI();
				return;
			} else {
				Battle::Shutdown(_player);
			};
		};
	}
	else if(CurrentMenu == UNDECIDED)
	{
		if(Battle::PlayersTurn == true)
		{
			Battle::UpdateUIPosition(_keys);
			if(CurrentMenu == FIGHT)
			{
				PokeEngine::ApplyDamage(&pokemon, PokeMath::CalculateDamage(Battle::GetActivePokemon().Level,
														Battle::GetActivePokemon().Attack,
														pokemon.Defence,
														MOVES_ARRAY[Battle::GetActivePokemon().MoveSet[SelectedAttack].Index].Power,
														1)); 
				Battle::ExecuteMoveEffect(&pokemon, &PlayersActivePokemon, MOVES_ARRAY[Battle::GetActivePokemon().MoveSet[SelectedAttack].Index].Effect);
				--PlayersActivePokemon.MoveSet[SelectedAttack].PP;
				Battle::PlayersTurn = false;
				Battle::ResetUI();
			}
			else if(CurrentMenu == RUN)
			{
				Battle::RunAway(_player);
			};
		}
		else
		{
			PokeEngine::ApplyDamage(&PlayersActivePokemon, PokeMath::CalculateDamage(pokemon.Level,
																					pokemon.Attack,
																					Battle::GetActivePokemon().Defence,
																					MOVES_ARRAY[pokemon.MoveSet[0].Index].Power,
																					1)); 
			Battle::ExecuteMoveEffect(&PlayersActivePokemon,&pokemon, MOVES_ARRAY[pokemon.MoveSet[0].Index].Effect);
			Battle::PlayersTurn = true;
			//ChosenAction = UNDECIDED;
		};
		return;
	};
	return;
};

void Battle::ExecuteMoveEffect(Pokemon* _target, Pokemon* _attacker,MOVE_EFFECTS _moveEffect)
{
	switch(_moveEffect)
	{
		case NO_ADDITIONAL_EFFECT:
			break;
		case ATTACK_DOWN1_EFFECT:
			_target->Attack = (int)(_target->Attack * 0.66);
			break;
		case ATTACK_UP1_EFFECT:
			_attacker->Attack = (int)(_attacker->Attack * 1.50);
			break;
		default:
			break;
	};
	return;
};

int BattleScreen::Load(SDL_Renderer* sdlRenderer)
{
	OpponentInfo = IMG_LoadTexture(sdlRenderer, "fightscreen/OpponentInfo.png");
	PlayerInfo = IMG_LoadTexture(sdlRenderer, "fightscreen/PlayerInfo.png");
	Frame = IMG_LoadTexture(sdlRenderer, "fightscreen/frame.png");
	HPBar = IMG_LoadTexture(sdlRenderer, "fightscreen/HPBar.png");
	arrow = IMG_LoadTexture(sdlRenderer, "fightscreen/arrow.png");
	Frame_Fight = IMG_LoadTexture(sdlRenderer, "fightscreen/frame_fight.png");
	if(!OpponentInfo || !PlayerInfo || !Frame || !HPBar || !arrow || !Frame_Fight)
		return -1;
	return 0;
};

void BattleScreen::Shutdown()
{
	SDL_DestroyTexture(BattleScreen::OpponentInfo);
	SDL_DestroyTexture(BattleScreen::PlayerInfo);
	SDL_DestroyTexture(BattleScreen::Frame);
	SDL_DestroyTexture(BattleScreen::HPBar);
	SDL_DestroyTexture(BattleScreen::arrow);
	SDL_DestroyTexture(BattleScreen::Frame_Fight);
	delete this;
	return;
};

bool Battle::HasOpponentActivePokemonFainted()
{
	if(Battle::GetOpponentHP() <= 0)
	{
		return true;
	}
	else
	{
		return false;
	};
};

bool Battle::HasActivePokemonFainted()
{
	if(Battle::GetActivePokemon().CurrHP <= 0)
	{
		return true;
	}
	else
	{
		return false;
	};
};

void Battle::UpdateUIPosition(Keys* _keys)
{
	
	if(_keys->W)
	{
		if(MenuDepth == 0)
		{
			if(SelectedMenuItem != 0 && SelectedMenuItem != 1)
			{
				SelectedMenuItem -= 2;
			};
		} else if(MenuDepth == 1 && SelectedMenuItem == 0){
			if(SelectedAttack > 0)
			{
				SelectedAttack--;
			};
		};
	} 
	else if(_keys->S)
	{
		if(MenuDepth == 0)
		{
			if(SelectedMenuItem != 2 && SelectedMenuItem != 3)
			{
				SelectedMenuItem += 2;
			};
		} else if(MenuDepth == 1 && SelectedMenuItem == 0){
			if(SelectedAttack < 3)
			{
				SelectedAttack++;
			};
		};
	}
	else if(_keys->A)
	{
		if(MenuDepth == 0)
		{
			if(SelectedMenuItem != 0 && SelectedMenuItem != 2)
			{
				SelectedMenuItem -= 1;
			};
		};
	}
	else if(_keys->D)
	{
		if(MenuDepth == 0)
		{
			if(SelectedMenuItem != 1 && SelectedMenuItem != 3)
			{
				SelectedMenuItem += 1;
			};
		};
	};
	if(_keys->ENTER)
	{
		if(MenuDepth < 1)
		{	
			MenuDepth++;
			if(SelectedMenuItem == 0)
			{
				//CurrentMenu = Battle::FIGHT;
			} 
			else if(SelectedMenuItem == 3)
			{
				CurrentMenu = Battle::RUN;
			};
		}
		else if(MenuDepth == 1 && SelectedMenuItem == 0)
		{
			Battle::CurrentMenu = FIGHT;
		};
	} 
	else if(_keys->BACKSPACE)
	{
		if(MenuDepth > 0)
		{
			Battle::CurrentMenu = UNDECIDED;
			MenuDepth = 0;
		};
	};
	return;
};

short int Battle::GetPlayerHP()
{
	return Battle::PlayersActivePokemon.CurrHP;
};

short int Battle::GetOpponentHP()
{
	return Battle::pokemon.CurrHP;
};

Pokemon Battle::GetActivePokemon()
{
	return Battle::PlayersActivePokemon;
};