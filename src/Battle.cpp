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

void Battle::SwitchActivePokemon(short int slot, Player* _player)
{
	Pokemon temporaryPkmn;

	temporaryPkmn = _player->GetParty()->Party[slot];
	_player->GetParty()->Party[slot] = Battle::PlayersActivePokemon;
	_player->GetParty()->Party[0] = temporaryPkmn;
	Battle::PlayersActivePokemon = _player->GetParty()->Party[0];

	return;
};

void Battle::Shutdown(Player* _player)
{
	if(_player->activeMessage)
	{
		if(_player->activeMessage->Active == true)
			return;
	};
	_player->GetParty()->Party[0].StatusCond = Battle::PlayersActivePokemon.StatusCond;
	_player->GetParty()->Party[0].CurrHP = Battle::PlayersActivePokemon.CurrHP;
	_player->GetParty()->Party[0].MoveSet[0].PP = Battle::PlayersActivePokemon.MoveSet[0].PP;
	_player->GetParty()->Party[0].MoveSet[1].PP = Battle::PlayersActivePokemon.MoveSet[1].PP;
	_player->GetParty()->Party[0].MoveSet[2].PP = Battle::PlayersActivePokemon.MoveSet[2].PP;
	_player->GetParty()->Party[0].MoveSet[3].PP = Battle::PlayersActivePokemon.MoveSet[3].PP;

	if(Battle::isTrainer == true)
	{
		switch(_player->currentOpponentID)
		{
			case 1:
				_player->beatTrainer1 = true;
				break;
			case 2:
				_player->beatTrainer2 = true;
				break;
			case 3:
				_player->beatTrainer3 = true;
				break;
			default:
				break;
		};
		_player->currentOpponentID = 0;
	};

	_player->SetInBattle(false);
	Mix_HaltMusic();
	delete this;
	return;
};

void Battle::Logic(Keys* _keys, Player* _player, bool* _quit)
{
	srand(time(NULL));
	if(HasOpponentActivePokemonFainted() == true && CurrentMenu != VICTORY)
	{
		CurrentMenu = VICTORY;
		_player->activeMessage->Reset();
	} 
	else if(HasActivePokemonFainted() == true)
	{
		for(size_t i = 1; i < _player->GetParty()->Party.size(); i++)
		{
			if(_player->GetParty()->Party[i].CurrHP > 0)
			{
				Battle::SwitchActivePokemon(i, _player);
				return;
			};
		};
		//GAME OVER.
		*_quit = true;
	};

	if(CurrentMenu == VICTORY)
	{
		if(Battle::isTrainer && opponentActivePkmn < (OpponentParty->Party.size()-1))
		{
			if(_player->activeMessage->Active==false && _player->activeMessage->Complete == false)
			{
				std::string zero = pokemon_names[pokemon.Index];
				std::string one = " FAINTED!";
				std::string complete = (zero + one);
				if(complete.length() < 15)
				{
					// do nothing
				} 
				else 
				{
					size_t tempsize = (15 - complete.length());
					for(size_t i = 0; i < tempsize; i++)
					{
						// Fix for a weird infinite loop
						if(tempsize > 40) break;
						zero += " ";
					};
				};
				_player->activeMessage = new Message( _strdup( (zero + one).c_str()) );
			}
			else if(_player->activeMessage->Complete == true)
			{
				Battle::pokemon = OpponentParty->Party[++opponentActivePkmn];
				Battle::PlayersTurn = true;
				Battle::ResetUI();
				_player->activeMessage->Reset();
				return;
			};
		} else {
			if(_player->activeMessage->Active==false)
			{
				_player->activeMessage = new Message("YOU WIN", &ShutdownBattle ,0.07f);
			};
			return;
		};
	}
	else if(CurrentMenu == UNDECIDED)
	{
		if(Battle::PlayersTurn == true)
		{
			if(_player->activeMessage->Active == false && _player->activeMessage->Complete == false)
			{
				Battle::UpdateUIPosition(_keys);
				if(CurrentMenu == FIGHT)
				{
					int tempDamage = PokeMath::CalculateDamage(Battle::GetActivePokemon().Level,
															Battle::GetActivePokemon().Attack,
															pokemon.Defence,
															MOVES_ARRAY[Battle::GetActivePokemon().MoveSet[SelectedAttack].Index].Power,
															1);
					PokeEngine::ApplyDamage(&pokemon, tempDamage); 
					Battle::ExecuteMoveEffect(&pokemon, &PlayersActivePokemon, MOVES_ARRAY[Battle::GetActivePokemon().MoveSet[SelectedAttack].Index].Effect,tempDamage);
					--PlayersActivePokemon.MoveSet[SelectedAttack].PP;
					
					std::string zero = pokemon_names[Battle::GetActivePokemon().Index];
					std::string one = " USED ";
					std::string two = MoveNames[Battle::GetActivePokemon().MoveSet[SelectedAttack].Index];
					std::string complete = (zero + one);
					if(complete.length() < 15)
					{
						size_t tempsize = (15 - complete.length());
						for(size_t i = 0; i < tempsize; i++)
						{
							one += " ";
						};
					};
					Battle::ResetUI();
					_player->activeMessage = new Message( _strdup( (zero + one + two).c_str()) );

				}
				else if(CurrentMenu == RUN)
				{
					if(this->isTrainer!=true)
					{
						Battle::RunAway(_player);
					}
					else
					{
						CurrentMenu = UNDECIDED;
						Battle::ResetUI();
					};
				};
			}
			else
			{
				if(_player->activeMessage->Complete == true)
				{
					Battle::PlayersTurn = false;
					_player->activeMessage->Reset();
				};
			};
		}
		else
		{
			if(_player->activeMessage->Active == false && _player->activeMessage->Complete == false)
			{
				int tempint = rand()%4;
				int tempDamage = PokeMath::CalculateDamage(			pokemon.Level,
																	pokemon.Attack,
																	Battle::GetActivePokemon().Defence,
																	MOVES_ARRAY[pokemon.MoveSet[tempint].Index].Power,
																	1);
				PokeEngine::ApplyDamage(&PlayersActivePokemon, tempDamage); 
				Battle::ExecuteMoveEffect(&PlayersActivePokemon,&pokemon, MOVES_ARRAY[pokemon.MoveSet[tempint].Index].Effect,tempDamage);
					
				std::string zero = pokemon_names[pokemon.Index];
				std::string one = " USED ";
				std::string two = MoveNames[pokemon.MoveSet[tempint].Index];
				std::string complete = (zero + one);
				if(complete.length() < 15)
				{
					size_t tempsize = (15 - complete.length());
					for(size_t i = 0; i < tempsize; i++)
					{
						one += " ";
					};
				};
				_player->activeMessage = new Message( _strdup( (zero + one + two).c_str()) );
			}
			else
			{
				if(_player->activeMessage->Complete == true)
				{
					_player->activeMessage->Reset();
					Battle::PlayersTurn = true;	
				};
			};
		};
		return;
	}
	else if(CurrentMenu == PKMN)
	{
		Battle::UpdateUIPosition(_keys);
		if(MenuDepth > 2)
		{
			Battle::SwitchActivePokemon(_player->selectedMenuItem,_player);
			Battle::ResetUI();
			Battle::PlayersTurn = false;
		};
	};
	return;
};

void Battle::ExecuteMoveEffect(Pokemon* _target, Pokemon* _attacker,MOVE_EFFECTS _moveEffect, int _damage)
{
	switch(_moveEffect)
	{
		case NO_ADDITIONAL_EFFECT:
			break;
		case DRAIN_HP_EFFECT:
			_attacker->CurrHP += (_damage/2);
			if(_attacker->CurrHP > _attacker->MaxHP)
			{
				_attacker->CurrHP = _attacker->MaxHP;
			};
			break;
		case POISON_SIDE_EFFECT1:
			if(rand()%100 < 30)
			{
				_target->StatusCond = POISON_COND;
			};
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
	pkmnSelectScreen = IMG_LoadTexture(sdlRenderer, "gfx/pkmnselection.png");
	HPBar_Outline = IMG_LoadTexture(sdlRenderer, "gfx/hpbar_outline.png");
	lvlslash = IMG_LoadTexture(sdlRenderer, "gfx/lvl-slash.png");
	pkmn_icon = IMG_LoadTexture(sdlRenderer, "gfx/pkmn.png");
	pokedex = IMG_LoadTexture(sdlRenderer, "gfx/pokedex.png");
	pokedexdetails = IMG_LoadTexture(sdlRenderer, "gfx/pokedexdetails.png");
	itemsMenu = IMG_LoadTexture(sdlRenderer, "gfx/itemsmenu.png");
	pkmnselection_box = IMG_LoadTexture(sdlRenderer, "gfx/pkmnselection_box.png");
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
	SDL_DestroyTexture(BattleScreen::pkmnSelectScreen);
	SDL_DestroyTexture(BattleScreen::HPBar_Outline);
	SDL_DestroyTexture(BattleScreen::lvlslash);
	SDL_DestroyTexture(BattleScreen::pkmn_icon);
	SDL_DestroyTexture(BattleScreen::pokedex);
	SDL_DestroyTexture(BattleScreen::pokedexdetails);
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
		}
		else if(MenuDepth >= 1 && SelectedMenuItem == 1)
		{
			Battle::CurrentMenu = PKMN;
			if(MenuDepth >= 2)
			{
				MenuDepth++;
			} 
			else 
			{
				MenuDepth++;
			};
		};
	} 
	else if(_keys->BACKSPACE)
	{
		if(MenuDepth > 0)
		{
			Battle::CurrentMenu = UNDECIDED;
			MenuDepth--;
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