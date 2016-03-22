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
		// To allow message to play before shutting down. Hacky, but works.
		if(_player->activeMessage->Active == true)
			return;
	};
	for(size_t i = 0; i < _player->GetParty()->Party.size(); i++)
	{
		_player->GetParty()->Party[i].StatusCond = STATUS_COND::NONE;
		_player->GetParty()->Party[i].CurrHP = _player->GetParty()->Party[i].MaxHP;
		_player->GetParty()->Party[i].MoveSet[0].PP = MOVES_ARRAY[Battle::PlayersActivePokemon.MoveSet[0].Index].PP;
		_player->GetParty()->Party[i].MoveSet[1].PP = MOVES_ARRAY[Battle::PlayersActivePokemon.MoveSet[1].Index].PP;
		_player->GetParty()->Party[i].MoveSet[2].PP = MOVES_ARRAY[Battle::PlayersActivePokemon.MoveSet[2].Index].PP;
		_player->GetParty()->Party[i].MoveSet[3].PP = MOVES_ARRAY[Battle::PlayersActivePokemon.MoveSet[3].Index].PP;
	};

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

void Battle::Logic(Keys* _keys, Player* _player, bool* _quit, SDL_Renderer* _sdlRenderer, GameStates* _GAMESTATE)
{
	if(_player->activeMessage->Active == true && _player->activeMessage->Complete == false)
	{
		return;
	};
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
		*_GAMESTATE = GAME_LOST;
		_player->activeMessage = new Message(Language_Master::StringToCString(Language_Master::FAILURE_TEXT));
	};

	if(CurrentMenu == VICTORY)
	{
		if(Battle::isTrainer && opponentActivePkmn < (OpponentParty->Party.size()-1))
		{
			if(_player->activeMessage->Active==false && _player->activeMessage->Complete == false)
			{
				std::string zero = pokemon_names[pokemon.Index];
				std::string one = " " + Language_Master::FAINTED;
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
				//const char* temp = Language_Master::StringToCString(Language_Master::YOU_WIN);
				_player->activeMessage = new Message(Language_Master::StringToCString(Language_Master::YOU_WIN), &ShutdownBattle ,0.07f);
			};
			return;
		};
	}
	else if(CurrentMenu == UNDECIDED)
	{
		if(Battle::PlayersTurn == true)
		{
			if((_player->activeMessage->Active == false && _player->activeMessage->Complete == false) || oppMissedMove == true)
			{
				missedMove = false;
				Battle::UpdateUIPosition(_keys);
				if(CurrentMenu == FIGHT)
				{
					// -1 == Has a status condition that prevents their turn
					if(StatusConditionUpdate(&PlayersActivePokemon, this) == -1)
					{
						return;
					};
					if(Battle::GetActivePokemon().MoveSet[SelectedAttack].PP == 0)
					{
						new Message("NO PP LEFT");
						Battle::ResetUI();
						return;
					};

					// calculate accuracy, return -1 if bad
					if(Battle::CalculateAccuracy(MOVES_ARRAY[Battle::GetActivePokemon().MoveSet[SelectedAttack].Index].Accuracy, playerAccuracy,opponentEvasion) == -1)
					{
						ResetUI();
						PlayersTurn = !PlayersTurn;
						missedMove = true;
						_player->activeMessage = new Message(Language_Master::StringToCString(Language_Master::YOU_MISSED));
						std::cout << "MOVE MISSED" << std::endl;
						return;
					};

					int tempDamage = PokeMath::CalculateDamage(Battle::GetActivePokemon().Level,
															Battle::GetActivePokemon().Attack,
															pokemon.Defence,
															MOVES_ARRAY[Battle::GetActivePokemon().MoveSet[SelectedAttack].Index].Power,
															1);
					Battle::ExecuteMoveEffect(&pokemon, &PlayersActivePokemon, Battle::GetActivePokemon().MoveSet[SelectedAttack].convertToMove(),tempDamage);
					--PlayersActivePokemon.MoveSet[SelectedAttack].PP;
					
					std::string zero = pokemon_names[Battle::GetActivePokemon().Index];
					std::string one = " " + Language_Master::USED + " ";
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
					oppMissedMove = false;

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
						_player->activeMessage = new Message(Language_Master::StringToCString(Language_Master::CANNOT_RUN));
						PlayersTurn = true;
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
			if((_player->activeMessage->Active == false && _player->activeMessage->Complete == false) || missedMove == true)
			{
				oppMissedMove = false;
				if(StatusConditionUpdate(&pokemon, this) == -1)
				{
					Battle::PlayersTurn = true;
					return;
				};
				int tempint = rand()%4;
				// calculate accuracy, return -1 if bad
				if(Battle::CalculateAccuracy(MOVES_ARRAY[pokemon.MoveSet[tempint].Index].Accuracy, opponentAccuracy,playerEvasion) == -1)
				{
					ResetUI();
					PlayersTurn = true;
					_player->activeMessage = new Message(Language_Master::StringToCString(Language_Master::THEY_MISSED));
					std::cout << "OPPONENT MOVE MISSED" << std::endl;
					oppMissedMove = true;
					return;
				};
				int tempDamage = PokeMath::CalculateDamage(			pokemon.Level,
																	pokemon.Attack,
																	Battle::GetActivePokemon().Defence,
																	MOVES_ARRAY[pokemon.MoveSet[tempint].Index].Power,
																	1);
				//PokeEngine::ApplyDamage(&PlayersActivePokemon, tempDamage); 
				Battle::ExecuteMoveEffect(&PlayersActivePokemon,&pokemon, pokemon.MoveSet[tempint].convertToMove(),tempDamage);
					
				std::string zero = pokemon_names[pokemon.Index];
				std::string one = " " + Language_Master::USED + " ";
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
				missedMove = false;
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

int BattleScreen::Load(SDL_Renderer* sdlRenderer)
{
	OpponentInfo = IMG_LoadTexture(sdlRenderer, "fightscreen/OpponentInfo.png");
	PlayerInfo = IMG_LoadTexture(sdlRenderer, "fightscreen/PlayerInfo.png");
	Frame = IMG_LoadTexture(sdlRenderer, std::string("./localizations/" + Language_Master::LANGUAGE + "/fightscreen/frame.png").c_str());
	HPBar = IMG_LoadTexture(sdlRenderer, "fightscreen/HPBar.png");
	arrow = IMG_LoadTexture(sdlRenderer, "fightscreen/arrow.png");
	Frame_Fight = IMG_LoadTexture(sdlRenderer, std::string("./localizations/" + Language_Master::LANGUAGE + "/fightscreen/frame_fight.png").c_str());
	pkmnSelectScreen = IMG_LoadTexture(sdlRenderer, std::string("./localizations/" + Language_Master::LANGUAGE + "/gfx/pkmnselection.png").c_str());
	HPBar_Outline = IMG_LoadTexture(sdlRenderer, "gfx/hpbar_outline.png");
	lvlslash = IMG_LoadTexture(sdlRenderer, "gfx/lvl-slash.png");
	pkmn_icon = IMG_LoadTexture(sdlRenderer, "gfx/pkmn.png");
	pokedex = IMG_LoadTexture(sdlRenderer, std::string("./localizations/" + Language_Master::LANGUAGE + "/gfx/pokedex.png").c_str());
	pokedexdetails = IMG_LoadTexture(sdlRenderer, "gfx/pokedexdetails.png");
	itemsMenu = IMG_LoadTexture(sdlRenderer, "gfx/itemsmenu.png");
	pkmnselection_box = IMG_LoadTexture(sdlRenderer, std::string("./localizations/" + Language_Master::LANGUAGE + "/gfx/pkmnselection_box.png").c_str());
	victory_screen = IMG_LoadTexture(sdlRenderer, "gfx/victory.png");
	failure_screen = IMG_LoadTexture(sdlRenderer, std::string("./localizations/" + Language_Master::LANGUAGE + "/gfx/failure.png").c_str());
	if(!OpponentInfo || !PlayerInfo || !Frame || !HPBar || !arrow || !Frame_Fight || !pkmnSelectScreen || !HPBar_Outline || !lvlslash || !pkmn_icon || !pokedex || !pokedexdetails || !itemsMenu || !pkmnselection_box || !victory_screen || !failure_screen)
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
	SDL_DestroyTexture(BattleScreen::itemsMenu);
	SDL_DestroyTexture(BattleScreen::pkmnselection_box);
	SDL_DestroyTexture(BattleScreen::victory_screen);
	SDL_DestroyTexture(BattleScreen::failure_screen);
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

void Battle::ExecuteMoveEffect(Pokemon* _target, Pokemon* _attacker, Move _move, int _damage)
{
	srand(time(NULL));
	short int tempint = 0;
	bool doDamage = true;

	short int modifiedDamage = _damage * Battle::CheckTypeMatch(TYPES(_move.Type),TYPES(_target->Type1));

	switch(_move.Effect)
	{
		case NO_ADDITIONAL_EFFECT:
			break;
		case BURN_SIDE_EFFECT1:
			if(rand()%100 < 30)
			{
				_target->StatusCond = BURNED;
			};
			break;
		case FREEZE_SIDE_EFFECT:
			if(rand()%100 < 30)
			{
				_target->StatusCond = FROZEN;
				_target->SleepTimer = 2;
			};
			break;
		case PARALYZE_SIDE_EFFECT1:
			if(rand()%100 < 30)
			{
				_target->StatusCond = PARALYZED;
				_target->SleepTimer = 2;
			};
			break;
		case MIRROR_MOVE_EFFECT:
			// lol not doing this; way too finicky
			break;
		case EXPLODE_EFFECT:
			_attacker->CurrHP = 0;
			break;
		case DREAM_EATER_EFFECT:
			if(_target->StatusCond == ASLEEP)
			{
				_attacker->CurrHP += (_damage*0.66);
				if(_attacker->CurrHP > _attacker->MaxHP)
				{
					_attacker->CurrHP = _attacker->MaxHP;
				};
			}
			else 
			{
				doDamage = false;		
			};
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
			_target->Attack -= 4;
			doDamage = false;
			break;
		case ATTACK_UP1_EFFECT:
			_attacker->Attack += 4;
			doDamage = false;
			break;
		case DEFENSE_UP1_EFFECT:
			_attacker->Defence += 4;
			doDamage = false;
			break;
		case SPEED_UP1_EFFECT:
			_attacker->Speed += 4;
			doDamage = false;
			break;
		case SPECIAL_UP1_EFFECT:
			_attacker->Special += 4;
			doDamage = false;
			break;
		case ACCURACY_UP1_EFFECT:
			//Accuracy += 4;
			doDamage = false;
			break;
		case EVASION_UP1_EFFECT:
			//opponentAccuracy += 4;
			doDamage = false;
			break;
		case PAY_DAY_EFFECT:
			// No cash = No effect
			break;
		case SWIFT_EFFECT:
			doDamage = true;
			break;
		case DEFENSE_DOWN1_EFFECT:
			_target->Defence -= 4;
			doDamage = false;
			break;
		case SPEED_DOWN1_EFFECT:
			_target->Speed -= 4;
			doDamage = false;
			break;
		case SPECIAL_DOWN1_EFFECT:
			_target->Special -= 4;
			doDamage = false;
			break;
		case ACCURACY_DOWN1_EFFECT:
			//Accuracy += 4;
			doDamage = false;
			break;
		case EVASION_DOWN1_EFFECT:
			//opponentAccuracy += 4;
			doDamage = false;
			break;
		case CONVERSION_EFFECT:
			_attacker->Type1 = _target->Type1;
			_attacker->Type2 = _target->Type2;
			doDamage = false;
			break;
		case HAZE_EFFECT:
			_attacker->MaxHP = PokeMath::CalculateStat(PokeMath::MAXHP, POKEDEX_REFERENCE[_attacker->Index].BaseHP, _attacker->Level);
			_attacker->Attack = PokeMath::CalculateStat(PokeMath::ATTACK, POKEDEX_REFERENCE[_attacker->Index].BaseAttack, _attacker->Level);
			_attacker->Defence = PokeMath::CalculateStat(PokeMath::DEFENCE, POKEDEX_REFERENCE[_attacker->Index].BaseDefense, _attacker->Level);
			_attacker->Speed = PokeMath::CalculateStat(PokeMath::SPEED, POKEDEX_REFERENCE[_attacker->Index].BaseSpeed, _attacker->Level);
			_attacker->Special = PokeMath::CalculateStat(PokeMath::SPECIAL, POKEDEX_REFERENCE[_attacker->Index].BaseSpecial, _attacker->Level);
			_target->MaxHP = PokeMath::CalculateStat(PokeMath::MAXHP, POKEDEX_REFERENCE[_target->Index].BaseHP, _target->Level);
			_target->Attack = PokeMath::CalculateStat(PokeMath::ATTACK, POKEDEX_REFERENCE[_target->Index].BaseAttack, _target->Level);
			_target->Defence = PokeMath::CalculateStat(PokeMath::DEFENCE, POKEDEX_REFERENCE[_target->Index].BaseDefense, _target->Level);
			_target->Speed = PokeMath::CalculateStat(PokeMath::SPEED, POKEDEX_REFERENCE[_target->Index].BaseSpeed, _target->Level);
			_target->Special = PokeMath::CalculateStat(PokeMath::SPECIAL, POKEDEX_REFERENCE[_target->Index].BaseSpecial, _target->Level);
			_target->StatusCond = STATUS_COND::NONE;
			doDamage = false;
			break;
		case BIDE_EFFECT:
			break;
		case THRASH_PETAL_DANCE_EFFECT:
			_damage *= 2;
			_attacker->StatusCond = STATUS_COND::CONFUSED;
			_attacker->SleepTimer = 2;
			doDamage = true;
			break;
		case SWITCH_AND_TELEPORT_EFFECT:
			doDamage = false;
			break;
		case TWO_TO_FIVE_ATTACKS_EFFECT:
			doDamage = false;
			PokeEngine::ApplyDamage(_target, _damage); 
			PokeEngine::ApplyDamage(_target, _damage); 
			tempint = rand()%3;
			for(short int i = 0; i < tempint; i++)
			{
				PokeEngine::ApplyDamage(_target, _damage); 
			};
			break;
		case FLINCH_SIDE_EFFECT1:
			// make skip other persons go? playersTurn * -1?
			break;
		case SLEEP_EFFECT:
			_target->StatusCond = STATUS_COND::ASLEEP;
			_target->SleepTimer += (rand()%2+1);
			break;
		case BURN_SIDE_EFFECT2:
			if(rand()%100 < 50)
			{
				_target->StatusCond = STATUS_COND::BURNED;
			};
			break;
		case POISON_SIDE_EFFECT2:
			if(rand()%100 < 50)
			{
				_target->StatusCond = STATUS_COND::POISON_COND;
			};
			break;
		case PARALYZE_SIDE_EFFECT2:
			if(rand()%100 < 50)
			{
				_target->StatusCond = STATUS_COND::PARALYZED;
				_target->SleepTimer = 2;
			};
			break;
		case FLINCH_SIDE_EFFECT2:
			break;
		case OHKO_EFFECT:
			if(_target->Speed > _attacker->Speed)
			{
				doDamage = false;
			}
			else
			{
				_target->CurrHP = 0;
			};
			break;
		case CHARGE_EFFECT:
			break;
		case SUPER_FANG_EFFECT:
			_target->CurrHP /= 2;
			doDamage = false;
			break;
		case SPECIAL_DAMAGE_EFFECT:
			_damage += _attacker->Level;
			break;
		case TRAPPING_EFFECT:
			break;
		case FLY_EFFECT:
			break;
		case ATTACK_TWICE_EFFECT:
			PokeEngine::ApplyDamage(_target, _damage); 
			PokeEngine::ApplyDamage(_target, _damage); 
			doDamage = false;
			break;
		case JUMP_KICK_EFFECT:
			break;
		case MIST_EFFECT:
			_attacker->MaxHP = PokeMath::CalculateStat(PokeMath::MAXHP, POKEDEX_REFERENCE[_attacker->Index].BaseHP, _attacker->Level);
			_attacker->Attack = PokeMath::CalculateStat(PokeMath::ATTACK, POKEDEX_REFERENCE[_attacker->Index].BaseAttack, _attacker->Level);
			_attacker->Defence = PokeMath::CalculateStat(PokeMath::DEFENCE, POKEDEX_REFERENCE[_attacker->Index].BaseDefense, _attacker->Level);
			_attacker->Speed = PokeMath::CalculateStat(PokeMath::SPEED, POKEDEX_REFERENCE[_attacker->Index].BaseSpeed, _attacker->Level);
			_attacker->Special = PokeMath::CalculateStat(PokeMath::SPECIAL, POKEDEX_REFERENCE[_attacker->Index].BaseSpecial, _attacker->Level);
			_target->MaxHP = PokeMath::CalculateStat(PokeMath::MAXHP, POKEDEX_REFERENCE[_target->Index].BaseHP, _target->Level);
			_target->Attack = PokeMath::CalculateStat(PokeMath::ATTACK, POKEDEX_REFERENCE[_target->Index].BaseAttack, _target->Level);
			_target->Defence = PokeMath::CalculateStat(PokeMath::DEFENCE, POKEDEX_REFERENCE[_target->Index].BaseDefense, _target->Level);
			_target->Speed = PokeMath::CalculateStat(PokeMath::SPEED, POKEDEX_REFERENCE[_target->Index].BaseSpeed, _target->Level);
			_target->Special = PokeMath::CalculateStat(PokeMath::SPECIAL, POKEDEX_REFERENCE[_target->Index].BaseSpecial, _target->Level);
			_target->StatusCond = STATUS_COND::NONE;
			doDamage = false;
			break;
		case FOCUS_ENERGY_EFFECT:
			// Literally nothing.
			doDamage = false;
			break;
		case RECOIL_EFFECT:
			_attacker->CurrHP -= (_damage*0.25);
			break;
		case CONFUSION_EFFECT:
			_target->StatusCond = STATUS_COND::CONFUSED;
			_target->SleepTimer = 2;
			doDamage = false;
			break;
		case ATTACK_UP2_EFFECT:
			_attacker->Attack += 8;
			doDamage = false;
			break;
		case DEFENSE_UP2_EFFECT:
			_attacker->Defence += 8;
			doDamage = false;
			break;
		case SPEED_UP2_EFFECT:
			_attacker->Speed += 8;
			doDamage = false;
			break;
		case SPECIAL_UP2_EFFECT:
			_attacker->Special += 8;
			doDamage = false;
			break;
		case HEAL_EFFECT:
			_attacker->CurrHP += (_attacker->MaxHP*0.5);
			if(_attacker->CurrHP > _attacker->MaxHP)
			{
				_attacker->CurrHP = _attacker->MaxHP;
			};
			if(_move.ID == REST && _attacker->StatusCond != ASLEEP)
			{
				_attacker->StatusCond = ASLEEP;
				_attacker->SleepTimer = 2;
				doDamage = false;
			};
			doDamage = false;
			break;
		case TRANSFORM_EFFECT:
			_attacker = _target;
			doDamage = false;
			break;
		case ATTACK_DOWN2_EFFECT:
			_target->Attack -= 8;
			doDamage = false;
			break;
		case DEFENSE_DOWN2_EFFECT:
			_target->Defence -= 8;
			doDamage = false;
			break;
		case SPEED_DOWN2_EFFECT:
			_target->Speed -= 8;
			doDamage = false;
			break;
		case SPECIAL_DOWN2_EFFECT:
			_target->Special -= 8;
			doDamage = false;
			break;
		case REFLECT_EFFECT:
			_attacker->Special *= 2;
			doDamage = false;
			break;
		case POISON_EFFECT:
			_target->StatusCond = STATUS_COND::POISON_COND;
			doDamage = false;
			break;
		case PARALYZE_EFFECT:
			_target->StatusCond = STATUS_COND::PARALYZED;
			_target->SleepTimer += (rand()%2+1);
			doDamage = false;
			break;
		case ATTACK_DOWN_SIDE_EFFECT:
			if(rand()%100 < 50)
			{
				_target->Attack -= 4;
			};
			break;
		case DEFENSE_DOWN_SIDE_EFFECT:
			if(rand()%100 < 50)
			{
				_target->Defence -= 4;
			};
			break;
		case SPEED_DOWN_SIDE_EFFECT:
			if(rand()%100 < 50)
			{
				_target->Speed -= 4;
			};
			break;
		case SPECIAL_DOWN_SIDE_EFFECT:
			if(rand()%100 < 50)
			{
				_target->Special -= 4;
			};
			break;
		case CONFUSION_SIDE_EFFECT:
			if(rand()%100 < 50)
			{
				_target->StatusCond = STATUS_COND::CONFUSED;
				_target->SleepTimer = 2;
			};
			break;
		case TWINEEDLE_EFFECT:
			doDamage = false;
			PokeEngine::ApplyDamage(_target, _damage); 
			if(rand()%100 < 20)
			{
				_target->StatusCond = STATUS_COND::POISON_COND;
			};
			PokeEngine::ApplyDamage(_target, _damage); 
			if(rand()%100 < 20)
			{
				_target->StatusCond = STATUS_COND::POISON_COND;
			};
			break;
		case SUBSTITUTE_EFFECT:
			doDamage = false;
			// What the what would even whatting go here?!
			break;
		case HYPER_BEAM_EFFECT:
			doDamage = true;
			// Miss a turn
			break;
		case RAGE_EFFECT:
			doDamage = true;
			// Inc damage every use
			break;
		case MIMIC_EFFECT:
			doDamage = true;
			// Copy random opponent move
			break;
		case METRONOME_EFFECT:
			doDamage = false;
			// Do a random move
			break;
		case LEECH_SEED_EFFECT:
			doDamage = true;
			// Steal hp over time
			break;
		case SPLASH_EFFECT:
			doDamage = false;
			// No damage at all
			break;
		case DISABLE_EFFECT:
			doDamage = false;
			// disable a random opponent move
			break;
		default:
			break;
	};
	if(doDamage = true)
	{
		PokeEngine::ApplyDamage(_target, _damage); 
	};
	return;
};

int StatusConditionUpdate(Pokemon* _pokemon, Battle* _battle)
{
	srand(unsigned int(time(NULL)));
	if((_pokemon->StatusCond == ASLEEP || _pokemon->StatusCond == PARALYZED || _pokemon->StatusCond == CONFUSED || _pokemon->StatusCond == FROZEN || _pokemon->StatusCond == BURNED || _pokemon->StatusCond == POISON_COND) && _pokemon->SleepTimer > 0)
	{
		switch(_pokemon->StatusCond)
		{
		case BURNED:
			_pokemon->CurrHP -= (_pokemon->MaxHP*0.0625);
			break;
		case POISON_COND:
			_pokemon->CurrHP -= (_pokemon->MaxHP*0.0625);
			break;
		case CONFUSED:		
			if(rand()%100 < 40)
			{
				PokeEngine::ApplyDamage(_pokemon, PokeMath::CalculateDamage(_pokemon->Level,
																_pokemon->Attack,
																_pokemon->Defence,
																40,
																1));
				_battle->ResetUI();
				if(_battle->PlayersTurn == true)
				{
					_battle->PlayersTurn = false;
				} 
				else 
				{
					_battle->PlayersTurn = true;
				};
				return -1;
			};
			_pokemon->SleepTimer--;
			break;
		default:
			_pokemon->SleepTimer--;
			_battle->ResetUI();
			if(_battle->PlayersTurn == true)
			{
				_battle->PlayersTurn = false;
			} 
			else 
			{
				_battle->PlayersTurn = true	;
			};
			return -1;
			break;
		};
	} 
	else if((_pokemon->StatusCond == ASLEEP || _pokemon->StatusCond == PARALYZED || _pokemon->StatusCond == CONFUSED || _pokemon->StatusCond == FROZEN) && _pokemon->SleepTimer <= 0)
	{
		_pokemon->SleepTimer = 0;
		_pokemon->StatusCond = NONE;
	};
	return 0;
};

short int Battle::CalculateAccuracy(short int _moveAcc, short int _userAcc, short int _defenderEvasion)
{
	// Probability = move accuracy * user accuracy / defender evasion;
	short int tempInt = (_moveAcc * _userAcc / _defenderEvasion);
 

	// If greater than 100, then it WILL hit
	if(tempInt >= 100)
		return 0;

	int randInt = rand()%100;
	std::cout << tempInt << " - " << randInt << std::endl;

	// if within bounds of probability, move hits
	if(randInt <= tempInt)
	{
		return 0;
	};

	// Otherwise nope, return -1
	return -1;
};

float Battle::CheckTypeMatch(TYPES _movetype, TYPES _opponentType)
{
	_movetype = Battle::TranslateTypeIntoLookup(_movetype);
	_opponentType = Battle::TranslateTypeIntoLookup(_opponentType);
	
	static const float WeaknessLookupTable[15][15] = 
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,0.5,0,1},
		{1,0.5,0.5,1,2,2,1,1,1,1,1,2,0.5,1,0.5},
		{1,2,0.5,1,0.5,1,1,1,2,1,1,1,2,1,0.5},
		{1,1,2,0.5,0.5,1,1,1,0,2,1,1,1,1,0.5},
		{1,0.5,2,1,0.5,1,1,0.5,2,0.5,1,0.5,2,1,0.5},
		{1,1,0.5,1,2,0.5,1,1,2,2,1,1,1,1,2},
		{2,1,1,1,1,2,1,0.5,1,0.5,0.5,0.5,2,0,1},
		{1,1,1,1,2,1,1,0.5,0.5,1,1,2,0.5,0.5,1},
		{1,2,1,2,0.5,1,1,2,1,0,1,0.5,2,1,1},
		{1,1,1,0.5,2,1,2,1,1,1,1,2,0.5,1,1},
		{1,1,1,1,1,1,2,2,1,1,0.5,1,1,1,1},
		{1,0.5,1,1,2,1,0.5,2,1,0.5,2,1,1,0.5,1},
		{1,2,1,1,1,2,0.5,1,0.5,2,1,2,1,1,1},
		{0,1,1,1,1,1,1,1,1,1,0,1,1,2,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,2}
	};

	float modifier = WeaknessLookupTable[_movetype][_opponentType];

	return modifier;
};

TYPES Battle::TranslateTypeIntoLookup(TYPES _type)
{
	switch(_type)
	{
	case FIGHTING:
		_type = FIRE;
		break;
	case FLYING:
		_type = WATER;
		break;
	case POISON:
		_type = ELECTRIC;
		break;
	case GROUND:
		_type = GRASS;
		break;
	case BIRD:
		_type = ICE;
		break;
	case BUG:
		_type = FIGHTING;
		break;
	case GHOST:
		_type = POISON;
		break;
	case FIRE:
		_type = GROUND;
		break;
	case WATER:
		_type = FLYING;
		break;
	case GRASS:
		_type = PSYCHIC;
		break;
	case ELECTRIC:
		_type = BUG;
		break;
	case PSYCHIC:
		_type = ROCK;
		break;
	case ICE:
		_type = GHOST;
		break;
	case DRAGON:
		_type = DRAGON;
		break;
	default:
		_type = NORMAL;
		break;
	};
	return _type;
};