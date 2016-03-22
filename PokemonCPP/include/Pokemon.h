#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "Moves.h"
#include <algorithm>
#include "PokeMath.h"
/*

Character				1	-128			127
Unsigned Char			1	0				255
Signed Char				1	-128			127
Integer					4	-2,147,483,648	2,147,483,647
Signed Int				4	0				4,294,967,295
Unsigned Int			4	-2,147,483,648	2,147,483,647
Short Int				2	-32,768			32,767
Signed short Int		2	0				65,535
Unsigned Short Int		2	-32,768			32,767
Long Int				4	-2,147,483,648	2,147,483,647
Signed Long Int			8	0				4,294,967,295
Unsigned Long Int		8	-2,147,483,648	2,147,483,647
Float					4	1.8E-38			3.4E+38
Double					8	2.2E-308		1.8E+308
Long Double				8	2.2E-308		1.8E+308
Bool					1	True/False		True/False
Wchar_t				2 or 4	0				65,535
*/
#pragma pack(1)


const std::string pokemon_names[151] = 
{
	"ABRA",
	"AERODACTYL",
	"ALAKAZAM",
	"ARBOK",
	"ARCANINE",
	"ARTICUNO",
	"BEEDRILL",
	"BELLSPROUT",
	"BLASTOISE",
	"BULBASAUR",
	"BUTTERFREE",
	"CATERPIE",
	"CHANSEY",
	"CHARIZARD",
	"CHARMANDER",
	"CHARMELEON",
	"CLEFABLE",
	"CLEFAIRY",
	"CLOYSTER",
	"CUBONE",
	"DEWGONG",
	"DIGLETT",
	"DITTO",
	"DODRIO",
	"DODUO",
	"DRAGONAIR",
	"DRAGONITE",
	"DRATINI",
	"DROWZEE",
	"DUGTRIO",
	"EEVEE",
	"EKANS",
	"ELECTABUZZ",
	"ELECTRODE",
	"EXEGGCUTE",
	"EXEGGUTOR",
	"FARFETCHD",
	"FEAROW",
	"FLAREON",
	"GASTLY",
	"GENGAR",
	"GEODUDE",
	"GLOOM",
	"GOLBAT",
	"GOLDEEN",
	"GOLDUCK",
	"GOLEM",
	"GRAVELER",
	"GRIMER",
	"GROWLITHE",
	"GYARADOS",
	"HAUNTER",
	"HITMONCHAN",
	"HITMONLEE",
	"HORSEA",
	"HYPNO",
	"IVYSAUR",
	"JIGGLYPUFF",
	"JOLTEON",
	"JYNX",
	"KABUTO",
	"KABUTOPS",
	"KADABRA",
	"KAKUNA",
	"KANGASKHAN",
	"KINGLER",
	"KOFFING",
	"KRABBY",
	"LAPRAS",
	"LICKITUNG",
	"MACHAMP",
	"MACHOKE",
	"MACHOP",
	"MAGIKARP",
	"MAGMAR",
	"MAGNEMITE",
	"MAGNETON",
	"MANKEY",
	"MAROWAK",
	"MEOWTH",
	"METAPOD",
	"MEW",
	"MEWTWO",
	"MOLTRES",
	"MR_MIME",
	"MUK",
	"NIDOKING",
	"NIDOQUEEN",
	"NIDORAN_F",
	"NIDORAN_M",
	"NIDORINA",
	"NIDORINO",
	"NINETALES",
	"ODDISH",
	"OMANYTE",
	"OMASTAR",
	"ONIX",
	"PARAS",
	"PARASECT",
	"PERSIAN",
	"PIDGEOT",
	"PIDGEOTTO",
	"PIDGEY",
	"PIKACHU",
	"PINSIR",
	"POLIWAG",
	"POLIWHIRL",
	"POLIWRATH",
	"PONYTA",
	"PORYGON",
	"PRIMEAPE",
	"PSYDUCK",
	"RAICHU",
	"RAPIDASH",
	"RATICATE",
	"RATTATA",
	"RHYDON",
	"RHYHORN",
	"SANDSHREW",
	"SANDSLASH",
	"SCYTHER",
	"SEADRA",
	"SEAKING",
	"SEEL",
	"SHELLDER",
	"SLOWBRO",
	"SLOWPOKE",
	"SNORLAX",
	"SPEAROW",
	"SQUIRTLE",
	"STARMIE",
	"STARYU",
	"TANGELA",
	"TAUROS",
	"TENTACOOL",
	"TENTACRUEL",
	"VAPOREON",
	"VENOMOTH",
	"VENONAT",
	"VENUSAUR",
	"VICTREEBEL",
	"VILEPLUME",
	"VOLTORB",
	"VULPIX",
	"WARTORTLE",
	"WEEDLE",
	"WEEPINBELL",
	"WEEZING",
	"WIGGLYTUFF",
	"ZAPDOS",
	"ZUBAT"
};

const std::string ASM_FILENAMES[151] = 
{
"abra.asm",
"aerodactyl.asm",
"alakazam.asm",
"arbok.asm",
"arcanine.asm",
"articuno.asm",
"beedrill.asm",
"bellsprout.asm",
"blastoise.asm",
"bulbasaur.asm",
"butterfree.asm",
"caterpie.asm",
"chansey.asm",
"charizard.asm",
"charmander.asm",
"charmeleon.asm",
"clefable.asm",
"clefairy.asm",
"cloyster.asm",
"cubone.asm",
"dewgong.asm",
"diglett.asm",
"ditto.asm",
"dodrio.asm",
"doduo.asm",
"dragonair.asm",
"dragonite.asm",
"dratini.asm",
"drowzee.asm",
"dugtrio.asm",
"eevee.asm",
"ekans.asm",
"electabuzz.asm",
"electrode.asm",
"exeggcute.asm",
"exeggutor.asm",
"farfetchd.asm",
"fearow.asm",
"flareon.asm",
"gastly.asm",
"gengar.asm",
"geodude.asm",
"gloom.asm",
"golbat.asm",
"goldeen.asm",
"golduck.asm",
"golem.asm",
"graveler.asm",
"grimer.asm",
"growlithe.asm",
"gyarados.asm",
"haunter.asm",
"hitmonchan.asm",
"hitmonlee.asm",
"horsea.asm",
"hypno.asm",
"ivysaur.asm",
"jigglypuff.asm",
"jolteon.asm",
"jynx.asm",
"kabuto.asm",
"kabutops.asm",
"kadabra.asm",
"kakuna.asm",
"kangaskhan.asm",
"kingler.asm",
"koffing.asm",
"krabby.asm",
"lapras.asm",
"lickitung.asm",
"machamp.asm",
"machoke.asm",
"machop.asm",
"magikarp.asm",
"magmar.asm",
"magnemite.asm",
"magneton.asm",
"mankey.asm",
"marowak.asm",
"meowth.asm",
"metapod.asm",
"mew.asm",
"mewtwo.asm",
"moltres.asm",
"mrmime.asm",
"muk.asm",
"nidoking.asm",
"nidoqueen.asm",
"nidoranf.asm",
"nidoranm.asm",
"nidorina.asm",
"nidorino.asm",
"ninetails.asm",
"oddish.asm",
"omanyte.asm",
"omastar.asm",
"onix.asm",
"paras.asm",
"parasect.asm",
"persian.asm",
"pidgeot.asm",
"pidgeotto.asm",
"pidgey.asm",
"pikachu.asm",
"pinsir.asm",
"poliwag.asm",
"poliwhirl.asm",
"poliwrath.asm",
"ponyta.asm",
"porygon.asm",
"primeape.asm",
"psyduck.asm",
"raichu.asm",
"rapidash.asm",
"raticate.asm",
"rattata.asm",
"rhydon.asm",
"rhyhorn.asm",
"sandshrew.asm",
"sandslash.asm",
"scyther.asm",
"seadra.asm",
"seaking.asm",
"seel.asm",
"shellder.asm",
"slowbro.asm",
"slowpoke.asm",
"snorlax.asm",
"spearow.asm",
"squirtle.asm",
"starmie.asm",
"staryu.asm",
"tangela.asm",
"tauros.asm",
"tentacool.asm",
"tentacruel.asm",
"vaporeon.asm",
"venomoth.asm",
"venonat.asm",
"venusaur.asm",
"victreebel.asm",
"vileplume.asm",
"voltorb.asm",
"vulpix.asm",
"wartortle.asm",
"weedle.asm",
"weepinbell.asm",
"weezing.asm",
"wigglytuff.asm",
"zapdos.asm",
"zubat.asm"
};

enum POKEMON_IDS
{
	ABRA,
	AERODACTYL,
	ALAKAZAM,
	ARBOK,
	ARCANINE,
	ARTICUNO,
	BEEDRILL,
	BELLSPROUT,
	BLASTOISE,
	BULBASAUR,
	BUTTERFREE,
	CATERPIE,
	CHANSEY,
	CHARIZARD,
	CHARMANDER,
	CHARMELEON,
	CLEFABLE,
	CLEFAIRY,
	CLOYSTER,
	CUBONE,
	DEWGONG,
	DIGLETT,
	DITTO,
	DODRIO,
	DODUO,
	DRAGONAIR,
	DRAGONITE,
	DRATINI,
	DROWZEE,
	DUGTRIO,
	EEVEE,
	EKANS,
	ELECTABUZZ,
	ELECTRODE,
	EXEGGCUTE,
	EXEGGUTOR,
	FARFETCHD,
	FEAROW,
	FLAREON,
	GASTLY,
	GENGAR,
	GEODUDE,
	GLOOM,
	GOLBAT,
	GOLDEEN,
	GOLDUCK,
	GOLEM,
	GRAVELER,
	GRIMER,
	GROWLITHE,
	GYARADOS,
	HAUNTER,
	HITMONCHAN,
	HITMONLEE,
	HORSEA,
	HYPNO,
	IVYSAUR,
	JIGGLYPUFF,
	JOLTEON,
	JYNX,
	KABUTO,
	KABUTOPS,
	KADABRA,
	KAKUNA,
	KANGASKHAN,
	KINGLER,
	KOFFING,
	KRABBY,
	LAPRAS,
	LICKITUNG,
	MACHAMP,
	MACHOKE,
	MACHOP,
	MAGIKARP,
	MAGMAR,
	MAGNEMITE,
	MAGNETON,
	MANKEY,
	MAROWAK,
	MEOWTH,
	METAPOD,
	MEW,
	MEWTWO,
	MOLTRES,
	MR_MIME,
	MUK,
	NIDOKING,
	NIDOQUEEN,
	NIDORAN_F,
	NIDORAN_M,
	NIDORINA,
	NIDORINO,
	NINETALES,
	ODDISH,
	OMANYTE,
	OMASTAR,
	ONIX,
	PARAS,
	PARASECT,
	PERSIAN,
	PIDGEOT,
	PIDGEOTTO,
	PIDGEY,
	PIKACHU,
	PINSIR,
	POLIWAG,
	POLIWHIRL,
	POLIWRATH,
	PONYTA,
	PORYGON,
	PRIMEAPE,
	PSYDUCK,
	RAICHU,
	RAPIDASH,
	RATICATE,
	RATTATA,
	RHYDON,
	RHYHORN,
	SANDSHREW,
	SANDSLASH,
	SCYTHER,
	SEADRA,
	SEAKING,
	SEEL,
	SHELLDER,
	SLOWBRO,
	SLOWPOKE,
	SNORLAX,
	SPEAROW,
	SQUIRTLE,
	STARMIE,
	STARYU,
	TANGELA,
	TAUROS,
	TENTACOOL,
	TENTACRUEL,
	VAPOREON,
	VENOMOTH,
	VENONAT,
	VENUSAUR,
	VICTREEBEL,
	VILEPLUME,
	VOLTORB,
	VULPIX,
	WARTORTLE,
	WEEDLE,
	WEEPINBELL,
	WEEZING,
	WIGGLYTUFF,
	ZAPDOS,
	ZUBAT
};

struct LoadedPokeSprites
{
	std::vector<SDL_Texture*> POKEMON_FRONT_SPRITES;
	std::vector<SDL_Texture*> POKEMON_BACK_SPRITES;
};

struct PokeMove
{
	unsigned char Index;
	unsigned char PP;
	Move convertToMove(void)
	{
		return MOVES_ARRAY[this->Index];
	};
};

struct PokedexPokemon
{
	/* Begin "faithful" data: */
	unsigned char DexNum;
	unsigned char BaseHP;
	unsigned char BaseAttack;
	unsigned char BaseDefense;
	unsigned char BaseSpeed;
	unsigned char BaseSpecial;
	unsigned char Type1;
	unsigned char Type2;
	unsigned char CatchRate;
	unsigned char BaseExpYield;
	unsigned char FontSpriteDimensions; //UNUSED
	SDL_Texture *FrontSprite;
	SDL_Texture *BackSprite;
	unsigned char Move1;
	unsigned char Move2;
	unsigned char Move3;
	unsigned char Move4;
	unsigned char GrowthRate;
	unsigned char TMHMFlag_1;
	unsigned char TMHMFlag_2;
	unsigned char TMHMFlag_3;
	unsigned char TMHMFlag_4;
	unsigned char TMHMFlag_5;
	unsigned char TMHMFlag_6;
	unsigned char TMHMFlag_7;
	/* End "faithful" data: */
};

extern PokedexPokemon POKEDEX_REFERENCE[151];

/* 
	Pokemon in Gen 1 were defined via a structure
	44 bytes in length.

	This is 45 bytes due to OrigTrainerID being 4
	bytes instead of 3. 
*/
struct Pokemon
{
	unsigned char Index;
	short int CurrHP;
	unsigned char LevelPC; // UNUSED?
	STATUS_COND StatusCond;
	unsigned char Type1;
	unsigned char Type2;
	unsigned char CatchRate_HeldItem;
	signed short int OrigTrainerID; //4 bytes instead of 3...
	signed int ExperiencePoints;
	signed short int HP_EV;
	signed short int ATTACK_EV;
	signed short int DEFENCE_EV;
	signed short int SPEED_EV;
	signed short int SPECIAL_EV;
	signed short int IVdata;
	PokeMove MoveSet[4];
	unsigned char Level;
	short int MaxHP;
	signed short int Attack;
	signed short int Defence;
	signed short int Speed;
	signed short int Special;
	signed short int SleepTimer;

	Pokemon()
	{
		// Standard init
	};

	Pokemon(int Index, int Level)
	{
		this->Index = Index; 
		this->Level = Level;
		this->CurrHP = PokeMath::CalculateStat(PokeMath::MAXHP, POKEDEX_REFERENCE[Index].BaseHP, this->Level);
		this->LevelPC = 1;
		this->StatusCond = NONE;
		this->Type1 = POKEDEX_REFERENCE[Index].Type1;
		this->Type2 = POKEDEX_REFERENCE[Index].Type2;
		this->CatchRate_HeldItem = POKEDEX_REFERENCE[0].CatchRate;
		this->MoveSet[0].Index = POKEDEX_REFERENCE[Index].Move1;
		this->MoveSet[1].Index = POKEDEX_REFERENCE[Index].Move2;
		this->MoveSet[2].Index = 0;
		this->MoveSet[3].Index = 0;
		this->OrigTrainerID = 0;
		this->ExperiencePoints = 0;
		this->HP_EV = 0;
		this->ATTACK_EV = 0;
		this->DEFENCE_EV = 0;
		this->SPEED_EV = 0;
		this->SPECIAL_EV = 0;
		this->IVdata = 0;
		this->MoveSet[0].PP = MOVES_ARRAY[this->MoveSet[0].Index].PP;
		this->MoveSet[1].PP = MOVES_ARRAY[this->MoveSet[1].Index].PP;
		this->MoveSet[2].PP = MOVES_ARRAY[this->MoveSet[2].Index].PP;
		this->MoveSet[3].PP = MOVES_ARRAY[this->MoveSet[3].Index].PP;
		this->MaxHP = PokeMath::CalculateStat(PokeMath::MAXHP, POKEDEX_REFERENCE[Index].BaseHP, this->Level);
		this->Attack = PokeMath::CalculateStat(PokeMath::ATTACK, POKEDEX_REFERENCE[Index].BaseAttack, this->Level);
		this->Defence = PokeMath::CalculateStat(PokeMath::DEFENCE, POKEDEX_REFERENCE[Index].BaseDefense, this->Level);
		this->Speed = PokeMath::CalculateStat(PokeMath::SPEED, POKEDEX_REFERENCE[Index].BaseSpeed, this->Level);
		this->Special = PokeMath::CalculateStat(PokeMath::SPECIAL, POKEDEX_REFERENCE[Index].BaseSpecial, this->Level);
		this->SleepTimer = 0;
	};

	Pokemon(int Index, int Level, int move1_index, int move2_index, int move3_index, int move4_index)
	{
		this->Index = Index; 
		this->Level = Level;
		this->CurrHP = PokeMath::CalculateStat(PokeMath::MAXHP, POKEDEX_REFERENCE[Index].BaseHP, this->Level);
		this->LevelPC = 1;
		this->StatusCond = NONE;
		this->Type1 = POKEDEX_REFERENCE[Index].Type1;
		this->Type2 = POKEDEX_REFERENCE[Index].Type2;
		this->CatchRate_HeldItem = POKEDEX_REFERENCE[0].CatchRate;
		this->MoveSet[0].Index = move1_index;
		this->MoveSet[1].Index = move2_index;
		this->MoveSet[2].Index = move3_index;
		this->MoveSet[3].Index = move4_index;
		this->OrigTrainerID = 0;
		this->ExperiencePoints = 0;
		this->HP_EV = 0;
		this->ATTACK_EV = 0;
		this->DEFENCE_EV = 0;
		this->SPEED_EV = 0;
		this->SPECIAL_EV = 0;
		this->IVdata = 0;
		this->MoveSet[0].PP = MOVES_ARRAY[move1_index].PP;
		this->MoveSet[1].PP = MOVES_ARRAY[move2_index].PP;
		this->MoveSet[2].PP = MOVES_ARRAY[move3_index].PP;
		this->MoveSet[3].PP = MOVES_ARRAY[move4_index].PP;
		this->MaxHP = PokeMath::CalculateStat(PokeMath::MAXHP, POKEDEX_REFERENCE[Index].BaseHP, this->Level);
		this->Attack = PokeMath::CalculateStat(PokeMath::ATTACK, POKEDEX_REFERENCE[Index].BaseAttack, this->Level);
		this->Defence = PokeMath::CalculateStat(PokeMath::DEFENCE, POKEDEX_REFERENCE[Index].BaseDefense, this->Level);
		this->Speed = PokeMath::CalculateStat(PokeMath::SPEED, POKEDEX_REFERENCE[Index].BaseSpeed, this->Level);
		this->Special = PokeMath::CalculateStat(PokeMath::SPECIAL, POKEDEX_REFERENCE[Index].BaseSpecial, this->Level);
		this->SleepTimer = 0;
	};
};

void InitPokemon(Pokemon *pokemon);

Pokemon CreatePokemon(
	unsigned char Index,
	short int CurrHP,
	unsigned char LevelPC,
	unsigned char StatusCond,
	unsigned char Type1,
	unsigned char Type2,
	unsigned char CatchRate_HeldItem,
	unsigned char Move1_index,
	unsigned char Move2_index,
	unsigned char Move3_index,
	unsigned char Move4_index,
	signed short int OrigTrainerID,
	signed int ExperiencePoints,
	signed short int HP_EV,
	signed short int ATTACK_EV,
	signed short int DEFENCE_EV,
	signed short int SPEED_EV,
	signed short int SPECIAL_EV,
	signed short int IVdata,
	unsigned char Move1_PP,
	unsigned char Move2_PP,
	unsigned char Move3_PP,
	unsigned char Move4_PP,
	unsigned char Level,
	short int MaxHP,
	signed short int Attack,
	signed short int Defence,
	signed short int Speed,
	signed short int Special);

Pokemon CreatePokemon(
	unsigned char Index);

Pokemon CreatePokemon(
	unsigned char Index,
	unsigned char Move1_index,
	unsigned char Move2_index,
	unsigned char Move3_index,
	unsigned char Move4_index
	);

int LoadPokemonFrontSprites(SDL_Renderer*, LoadedPokeSprites*);
int LoadPokemonBackSprites(SDL_Renderer*, LoadedPokeSprites*);
int LoadPokedexData(void);

#endif