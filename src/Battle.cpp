#include "Battle.h"

//void Battle::CreateBattle(PokeParty* _PlayerParty,Trainer* _OpponentTrainer)
//{
//	Battle::PlayerParty = _PlayerParty;
//	Battle::OpponentTrainer = _OpponentTrainer;
//	Battle::OpponentParty = _OpponentTrainer->Party;
//	return;
//};

void Battle::CreateBattle(PokeParty* _PlayerParty, Pokemon* _OpponentPokemon)
{
	Battle::PlayerParty = _PlayerParty;
	Battle::pokemon = _OpponentPokemon;
	Battle::SelectedMenuItem = 0;
	Battle::CurrentMenu = 0;
	Battle::SelectedAttack = 0;
	Battle::PlayersTurn = true;
	Battle::ChosenAction = UNDECIDED;
	return;
};

void Battle::ResetUI()
{
	Battle::ChosenAction = UNDECIDED;
	Battle::SelectedMenuItem = 0;
	Battle::CurrentMenu = 0;
	Battle::SelectedAttack = 0;
	return;
};

void Battle::Logic(Keys* _keys, Player* _player)
{
	if(Battle::PlayersTurn == true)
	{
		Battle::UpdateUIPosition(_keys);
		if(ChosenAction == ATTACK)
		{
			/*std::cout << CalculateDamage(_player->party.Party[_player->ActivePokemon].Level,
													_player->party.Party[_player->ActivePokemon].Attack,
													pokemon->Defence,MOVES_ARRAY[Battle::PlayerParty->Party[_player->ActivePokemon].Move1_index].Power,
													1) << std::endl << Battle::pokemon->CurrHP << std::endl;*/
			Battle::pokemon->CurrHP -= CalculateDamage(_player->party.Party[_player->ActivePokemon].Level,
													_player->party.Party[_player->ActivePokemon].Attack,
													pokemon->Defence,MOVES_ARRAY[Battle::PlayerParty->Party[_player->ActivePokemon].Move1_index].Power,
													1); 
			Battle::PlayersTurn = false;
			Battle::ResetUI();
		};
	}
	else
	{
		_player->party.Party[_player->ActivePokemon].CurrHP -= CalculateDamage(pokemon->Level,
																				pokemon->Attack,
																				_player->party.Party[_player->ActivePokemon].Defence,
																				MOVES_ARRAY[pokemon->Move1_index].Power,
																				1); 
		Battle::PlayersTurn = true;
		//ChosenAction = UNDECIDED;
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
	if(!OpponentInfo || !PlayerInfo || !Frame || !HPBar)
		return -1;
	return 0;
};

void Battle::UpdateUIPosition(Keys* _keys)
{
	
	if(_keys->W)
	{
		if(CurrentMenu == 0)
		{
			if(SelectedMenuItem != 0 && SelectedMenuItem != 1)
			{
				SelectedMenuItem -= 2;
			};
		} else if(CurrentMenu == 1){
			if(SelectedAttack > 0)
			{
				SelectedAttack--;
			};
		};
	} 
	else if(_keys->S)
	{
		if(CurrentMenu == 0)
		{
			if(SelectedMenuItem != 2 && SelectedMenuItem != 3)
			{
				SelectedMenuItem += 2;
			};
		} else if(CurrentMenu == 1){
			if(SelectedAttack < 3)
			{
				SelectedAttack++;
			};
		};
	}
	else if(_keys->A)
	{
		if(CurrentMenu == 0)
		{
			if(SelectedMenuItem != 0 && SelectedMenuItem != 2)
			{
				SelectedMenuItem -= 1;
			};
		};
	}
	else if(_keys->D)
	{
		if(CurrentMenu == 0)
		{
			if(SelectedMenuItem != 1 && SelectedMenuItem != 3)
			{
				SelectedMenuItem += 1;
			};
		};
	};
	if(_keys->ENTER)
	{
		if(CurrentMenu < 1)
		{	
			CurrentMenu++;
		}
		else if(CurrentMenu == 1)
		{
			Battle::ChosenAction = ATTACK;
		};
	} 
	else if(_keys->BACKSPACE)
	{
		if(CurrentMenu > 0)
			CurrentMenu--;
	};
	return;
};