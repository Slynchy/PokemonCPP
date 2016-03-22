/*
	PokeParser v1.1
	By Sam Lynch
	Amduat Games

	To be used with the contents 
	of "baseStats" folder of:
	https://github.com/pret/pokered

	Parses the ASM of each pkmn's
	baseStats and outputs a const 
	array for C++
*/


#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <algorithm>

#pragma region Globals
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

const std::string MoveNames[165] = 
{
	"POUND",
	"KARATE_CHOP",
	"DOUBLESLAP",
	"COMET_PUNCH",
	"MEGA_PUNCH",
	"PAY_DAY",
	"FIRE_PUNCH",
	"ICE_PUNCH" ,
	"THUNDERPUNCH",
	"SCRATCH",
	"VICEGRIP",
	"GUILLOTINE",
	"RAZOR_WIND",
	"SWORDS_DANCE",
	"CUT" ,
	"GUST",
	"WING_ATTACK",
	"WHIRLWIND" ,
	"FLY" ,
	"BIND",
	"SLAM",
	"VINE_WHIP" ,
	"STOMP",
	"DOUBLE_KICK",
	"MEGA_KICK" ,
	"JUMP_KICK" ,
	"ROLLING_KICK",
	"SAND_ATTACK",
	"HEADBUTT",
	"HORN_ATTACK",
	"FURY_ATTACK",
	"HORN_DRILL",
	"TACKLE" ,
	"BODY_SLAM" ,
	"WRAP",
	"TAKE_DOWN" ,
	"THRASH" ,
	"DOUBLE_EDGE",
	"TAIL_WHIP" ,
	"POISON_STING",
	"TWINEEDLE" ,
	"PIN_MISSILE",
	"LEER",
	"BITE",
	"GROWL",
	"ROAR",
	"SING",
	"SUPERSONIC",
	"SONICBOOM" ,
	"DISABLE",
	"ACID",
	"EMBER",
	"FLAMETHROWER",
	"MIST",
	"WATER_GUN" ,
	"HYDRO_PUMP",
	"SURF",
	"ICE_BEAM",
	"BLIZZARD",
	"PSYBEAM",
	"BUBBLEBEAM",
	"AURORA_BEAM",
	"HYPER_BEAM",
	"PECK",
	"DRILL_PECK",
	"SUBMISSION",
	"LOW_KICK",
	"COUNTER",
	"SEISMIC_TOSS",
	"STRENGTH",
	"ABSORB" ,
	"MEGA_DRAIN",
	"LEECH_SEED",
	"GROWTH" ,
	"RAZOR_LEAF",
	"SOLARBEAM" ,
	"POISONPOWDER",
	"STUN_SPORE",
	"SLEEP_POWDER",
	"PETAL_DANCE",
	"STRING_SHOT",
	"DRAGON_RAGE",
	"FIRE_SPIN" ,
	"THUNDERSHOCK",
	"THUNDERBOLT",
	"THUNDER_WAVE",
	"THUNDER",
	"ROCK_THROW",
	"EARTHQUAKE",
	"FISSURE",
	"DIG" ,
	"TOXIC",
	"CONFUSION" ,
	"PSYCHIC" ,
	"HYPNOSIS",
	"MEDITATE",
	"AGILITY",
	"QUICK_ATTACK",
	"RAGE",
	"TELEPORT",
	"NIGHT_SHADE",
	"MIMIC",
	"SCREECH",
	"DOUBLE_TEAM",
	"RECOVER",
	"HARDEN" ,
	"MINIMIZE",
	"SMOKESCREEN",
	"CONFUSE_RAY",
	"WITHDRAW",
	"DEFENSE_CURL",
	"BARRIER",
	"LIGHT_SCREEN",
	"HAZE",
	"REFLECT",
	"FOCUS_ENERGY",
	"BIDE",
	"METRONOME" ,
	"MIRROR_MOVE",
	"SELFDESTRUCT",
	"EGG_BOMB",
	"LICK",
	"SMOG",
	"SLUDGE" ,
	"BONE_CLUB" ,
	"FIRE_BLAST",
	"WATERFALL" ,
	"CLAMP",
	"SWIFT",
	"SKULL_BASH",
	"SPIKE_CANNON",
	"CONSTRICT" ,
	"AMNESIA",
	"KINESIS",
	"SOFTBOILED",
	"HI_JUMP_KICK",
	"GLARE",
	"DREAM_EATER",
	"POISON_GAS",
	"BARRAGE",
	"LEECH_LIFE",
	"LOVELY_KISS",
	"SKY_ATTACK",
	"TRANSFORM" ,
	"BUBBLE" ,
	"DIZZY_PUNCH",
	"SPORE",
	"FLASH",
	"PSYWAVE",
	"SPLASH" ,
	"ACID_ARMOR",
	"CRABHAMMER",
	"EXPLOSION" ,
	"FURY_SWIPES",
	"BONEMERANG",
	"REST",
	"ROCK_SLIDE",
	"HYPER_FANG",
	"SHARPEN",
	"CONVERSION",
	"TRI_ATTACK",
	"SUPER_FANG",
	"SLASH",
	"SUBSTITUTE",
	"STRUGGLE"
};

enum TYPES 
{
	NORMAL , 
	FIGHTING , 
	FLYING , 
	POISON ,
	GROUND ,
	ROCK ,
	BIRD ,
	BUG ,
	GHOST ,
	BLANK_1 ,
	BLANK_2 ,
	BLANK_3 ,
	BLANK_4 ,
	BLANK_5 ,
	FIRE ,
	WATER ,
	GRASS ,
	ELECTRIC ,
	PSYCHIC ,
	ICE ,
	DRAGON
};

const std::string TYPE_STRINGS[21] =
{
	"NORMAL" , 
	"FIGHTING" , 
	"FLYING" , 
	"POISON" ,
	"GROUND" ,
	"ROCK" ,
	"BIRD" ,
	"BUG" ,
	"GHOST" ,
	"BLANK_1" ,
	"BLANK_2" ,
	"BLANK_3" ,
	"BLANK_4" ,
	"BLANK_5" ,
	"FIRE" ,
	"WATER" ,
	"GRASS",
	"ELECTRIC" ,
	"PSYCHIC" ,
	"ICE" ,
	"DRAGON"
};

enum MoveIDs
{
	POUND        ,
	KARATE_CHOP  ,
	DOUBLESLAP   ,
	COMET_PUNCH  ,
	MEGA_PUNCH   ,
	PAY_DAY      ,
	FIRE_PUNCH   ,
	ICE_PUNCH    ,
	THUNDERPUNCH ,
	SCRATCH      ,
	VICEGRIP     ,
	GUILLOTINE   ,
	RAZOR_WIND   ,
	SWORDS_DANCE ,
	CUT          ,
	GUST         ,
	WING_ATTACK  ,
	WHIRLWIND    ,
	FLY          ,
	BIND         ,
	SLAM         ,
	VINE_WHIP    ,
	STOMP        ,
	DOUBLE_KICK  ,
	MEGA_KICK    ,
	JUMP_KICK    ,
	ROLLING_KICK ,
	SAND_ATTACK  ,
	HEADBUTT     ,
	HORN_ATTACK  ,
	FURY_ATTACK  ,
	HORN_DRILL   ,
	TACKLE       ,
	BODY_SLAM    ,
	WRAP         ,
	TAKE_DOWN    ,
	THRASH       ,
	DOUBLE_EDGE  ,
	TAIL_WHIP    ,
	POISON_STING ,
	TWINEEDLE    ,
	PIN_MISSILE  ,
	LEER         ,
	BITE         ,
	GROWL        ,
	ROAR         ,
	SING_m         ,
	SUPERSONIC   ,
	SONICBOOM    ,
	DISABLE      ,
	ACID         ,
	EMBER        ,
	FLAMETHROWER ,
	MIST         ,
	WATER_GUN    ,
	HYDRO_PUMP   ,
	SURF         ,
	ICE_BEAM     ,
	BLIZZARD     ,
	PSYBEAM      ,
	BUBBLEBEAM   ,
	AURORA_BEAM  ,
	HYPER_BEAM   ,
	PECK         ,
	DRILL_PECK   ,
	SUBMISSION   ,
	LOW_KICK     ,
	COUNTER      ,
	SEISMIC_TOSS ,
	STRENGTH     ,
	ABSORB       ,
	MEGA_DRAIN   ,
	LEECH_SEED   ,
	GROWTH       ,
	RAZOR_LEAF   ,
	SOLARBEAM    ,
	POISONPOWDER ,
	STUN_SPORE   ,
	SLEEP_POWDER ,
	PETAL_DANCE  ,
	STRING_SHOT  ,
	DRAGON_RAGE  ,
	FIRE_SPIN    ,
	THUNDERSHOCK ,
	THUNDERBOLT  ,
	THUNDER_WAVE ,
	THUNDER      ,
	ROCK_THROW   ,
	EARTHQUAKE   ,
	FISSURE      ,
	DIG          ,
	TOXIC        ,
	CONFUSION    ,
	PSYCHIC_m    ,
	HYPNOSIS     ,
	MEDITATE     ,
	AGILITY      ,
	QUICK_ATTACK ,
	RAGE         ,
	TELEPORT     ,
	NIGHT_SHADE  ,
	MIMIC        ,
	SCREECH      ,
	DOUBLE_TEAM  ,
	RECOVER      ,
	HARDEN       ,
	MINIMIZE     ,
	SMOKESCREEN  ,
	CONFUSE_RAY  ,
	WITHDRAW     ,
	DEFENSE_CURL ,
	BARRIER      ,
	LIGHT_SCREEN ,
	HAZE         ,
	REFLECT      ,
	FOCUS_ENERGY ,
	BIDE         ,
	METRONOME    ,
	MIRROR_MOVE  ,
	SELFDESTRUCT ,
	EGG_BOMB     ,
	LICK         ,
	SMOG         ,
	SLUDGE       ,
	BONE_CLUB    ,
	FIRE_BLAST   ,
	WATERFALL    ,
	CLAMP        ,
	SWIFT        ,
	SKULL_BASH   ,
	SPIKE_CANNON ,
	CONSTRICT    ,
	AMNESIA      ,
	KINESIS      ,
	SOFTBOILED   ,
	HI_JUMP_KICK ,
	GLARE        ,
	DREAM_EATER  ,
	POISON_GAS   ,
	BARRAGE      ,
	LEECH_LIFE  ,
	LOVELY_KISS,
	SKY_ATTACK  ,
	TRANSFORM    ,
	BUBBLE       ,
	DIZZY_PUNCH  ,
	SPORE        ,
	FLASH        ,
	PSYWAVE      ,
	SPLASH       ,
	ACID_ARMOR   ,
	CRABHAMMER   ,
	EXPLOSION    ,
	FURY_SWIPES  ,
	BONEMERANG   ,
	REST         ,
	ROCK_SLIDE   ,
	HYPER_FANG   ,
	SHARPEN      ,
	CONVERSION  ,
	TRI_ATTACK   ,
	SUPER_FANG   ,
	SLASH        ,
	SUBSTITUTE  ,
	STRUGGLE
};

struct PokedexPokemon
{
	/* Begin "faithful" data: */
	std::string DexNum;
	unsigned char BaseHP;
	unsigned char BaseAttack;
	unsigned char BaseDefense;
	unsigned char BaseSpeed;
	unsigned char BaseSpecial;
	unsigned char Type1;
	unsigned char Type2;
	unsigned char CatchRate;
	unsigned char BaseExpYield;
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
#pragma endregion

int GetStat(std::fstream*);
TYPES GetType(std::fstream*);
MoveIDs GetMove(std::fstream*);
TYPES HashTypeString (std::string const& inString);
std::string WriteEntry(PokedexPokemon*);
PokedexPokemon* LoadData(std::fstream* fs);
void WriteDataToBinary(PokedexPokemon* _array[151]);

int main(void)
{
	std::string Result = "";
	Result = "const PokedexPokemon POKEDEX_REFERENCE[151] = ";
	Result.append("\n{");

	PokedexPokemon* Test[151];

	for(int i = 0; i < 151; i++)
	{
		std::string TempFilePath = ("asm_files/" + ASM_FILENAMES[i]);
		std::fstream fs;
		if(fs)
		{
			fs.open(TempFilePath,std::fstream::in | std::fstream::binary);
			Test[i] = LoadData(&fs);
			fs.close();
			Result.append(WriteEntry(Test[i]));
		};
	};


	Result.append(",\n	");
	
	Result.append("}\n};");


	std::cout << Result;
	
	std::fstream output_fs;
	output_fs.open("output.txt",std::fstream::out | std::fstream::binary);
	output_fs << Result;
	output_fs.close();

	output_fs.open("output_enum.txt",std::fstream::out | std::fstream::binary);
	output_fs << "enum POKEMON_IDS\n{\n	";
	for(int i = 0; i < 151; i++)
	{
		output_fs << Test[i]->DexNum << ",\n	";
	};
	output_fs.close();

	output_fs.open("output_strings.txt",std::fstream::out | std::fstream::binary);
	output_fs << "const std::string pokemon_names[151] = \n{\n	";
	for(int i = 0; i < 151; i++)
	{
		output_fs << "\"" << Test[i]->DexNum << "\",\n	";
	};
	output_fs << "};";
	output_fs.close();

	//std::transform(data.begin(), data.end(), data.begin(), ::tolower);

	output_fs.open("output_filenames.txt",std::fstream::out | std::fstream::binary);
	output_fs << "const std::string pokemon_filenames[151] =  \n{\n	";
	for(int i = 0; i < 151; i++)
	{
		std::string tempString = Test[i]->DexNum;
		std::transform(tempString.begin(), tempString.end(), tempString.begin(), ::tolower);
		output_fs << "\"" << tempString << ".png" << "\",\n	";
	};
	output_fs << "};";
	output_fs.close();

	WriteDataToBinary(Test);

	_getch();
	for(int i = 0; i < 151; i++)
	{
		delete Test[i];
	};
	return 0;
};

int GetStat(std::fstream* _f)
{
	std::string dummyLine;
	int tempInt = 0;
	*_f >> dummyLine;
	
	*_f >> tempInt;
	
	getline(*_f, dummyLine);

	return tempInt;
};

TYPES GetType(std::fstream* _f)
{
	std::string dummyLine;
	std::string tempString;

	TYPES parsedType = NORMAL;

	int tempInt = 0;
	*_f >> dummyLine;
	
	*_f >> tempString;

	parsedType = HashTypeString(tempString);
	
	getline(*_f, dummyLine);

	return parsedType;
};

TYPES HashTypeString (std::string const& inString) {
    if (inString == "NORMAL") return NORMAL;
    if (inString == "FIGHTING") return FIGHTING;
    if (inString == "FLYING") return FLYING;
    if (inString == "POISON") return POISON;
    if (inString == "GROUND") return GROUND;
    if (inString == "ROCK") return ROCK;
    if (inString == "BIRD") return BIRD;
    if (inString == "BUG") return BUG;
    if (inString == "GHOST") return GHOST;
    if (inString == "BLANK_1") return BLANK_1;
    if (inString == "BLANK_2") return BLANK_2;
    if (inString == "BLANK_3") return BLANK_3;
    if (inString == "BLANK_4") return BLANK_4;
    if (inString == "BLANK_5") return BLANK_5;
    if (inString == "FIRE") return FIRE;
    if (inString == "WATER") return WATER;
    if (inString == "GRASS") return GRASS;
    if (inString == "ELECTRIC") return ELECTRIC;
	if (inString == "PSYCHIC") return TYPES::PSYCHIC;
    if (inString == "ICE") return ICE;
    if (inString == "DRAGON") return DRAGON;
	return NORMAL;
}

MoveIDs GetMove(std::fstream* _f)
{
	std::string dummyLine;
	int tempInt = 0;
	*_f >> dummyLine;
	*_f >> dummyLine;

	for(int i = 0; i < 165; i++)
	{
		if(dummyLine == MoveNames[i] || dummyLine == "0")
		{
			tempInt = i;
			break;
		};
	};
	getline(*_f, dummyLine);

	return (MoveIDs)tempInt;
};

std::string WriteEntry(PokedexPokemon* Test)
{
	std::string Result;

	Result.append("\n	{\n		");
	Result.append(Test->DexNum);
	Result.append(",\n		");
	Result.append(std::to_string(Test->BaseHP));
	Result.append(",\n		");
	Result.append(std::to_string(Test->BaseAttack));
	Result.append(",\n		");
	Result.append(std::to_string(Test->BaseDefense));
	Result.append(",\n		");
	Result.append(std::to_string(Test->BaseSpeed));
	Result.append(",\n		");
	Result.append(std::to_string(Test->BaseSpecial));
	Result.append(",\n		");
	Result.append(TYPE_STRINGS[Test->Type1]);
	Result.append(",\n		");
	Result.append(TYPE_STRINGS[Test->Type2]);
	Result.append(",\n		");
	Result.append(std::to_string(Test->CatchRate));
	Result.append(",\n		");
	Result.append(std::to_string(Test->BaseExpYield));
	Result.append(",\n		");
	Result.append("0");
	Result.append(",\n		");
	Result.append("0");
	Result.append(",\n		");
	Result.append("0");
	Result.append(",\n		");
	if(Test->Move1 == 0)
	{
		Result.append("0");
	} 
	else
	{
		Result.append(MoveNames[Test->Move1]);
	};
	Result.append(",\n		");
	if(Test->Move2 == 0)
	{
		Result.append("0");
	} 
	else
	{
		Result.append(MoveNames[Test->Move2]);
	};
	Result.append(",\n		");
	if(Test->Move3 == 0)
	{
		Result.append("0");
	} 
	else
	{
		Result.append(MoveNames[Test->Move3]);
	};
	Result.append(",\n		");
	if(Test->Move4 == 0)
	{
		Result.append("0");
	} 
	else
	{
		Result.append(MoveNames[Test->Move4]);
	};
	Result.append(",\n		");
	Result.append(std::to_string(Test->GrowthRate));
	Result.append(",\n		");
	Result.append("0");
	Result.append(",\n		");
	Result.append("0");
	Result.append(",\n		");
	Result.append("0");
	Result.append(",\n		");
	Result.append("0");
	Result.append(",\n		");
	Result.append("0");
	Result.append(",\n		");
	Result.append("0");
	Result.append(",\n		");
	Result.append("0");
	Result.append("\n	},");
	return Result;
};

PokedexPokemon* LoadData(std::fstream* fs)
{
	PokedexPokemon* Test = new PokedexPokemon;
	std::string dummyLine;

	getline(*fs, dummyLine);
	*fs >> dummyLine; // DB
	*fs >> Test->DexNum;

	Test->DexNum.erase(0,4);

	getline(*fs, dummyLine);

	Test->BaseHP = GetStat(fs);
	Test->BaseAttack = GetStat(fs);
	Test->BaseDefense = GetStat(fs);
	Test->BaseSpeed = GetStat(fs);
	Test->BaseSpecial = GetStat(fs);
	Test->Type1 = GetType(fs);
	Test->Type2 = GetType(fs);
	Test->CatchRate = GetStat(fs);
	Test->BaseExpYield = GetStat(fs);
	
	getline(*fs, dummyLine); // incbin
	getline(*fs, dummyLine); // pic front
	getline(*fs, dummyLine); // pic back
	getline(*fs, dummyLine); // attax known

	Test->Move1 = GetMove(fs);
	Test->Move2 = GetMove(fs);
	Test->Move3 = GetMove(fs);
	Test->Move4 = GetMove(fs);

	Test->GrowthRate = GetStat(fs);

	return Test;
};

void WriteDataToBinary(PokedexPokemon* _array[151])
{
	std::ofstream ofs ("pokedex.bin", std::fstream::binary);
	for(int i = 0; i < 151; i++)
	{
		ofs.write( reinterpret_cast <const char*> (&_array[i]->BaseHP), sizeof( _array[i]->BaseHP ) );
		ofs.write( reinterpret_cast <const char*> (&_array[i]->BaseAttack), sizeof( _array[i]->BaseAttack ) );
		ofs.write( reinterpret_cast <const char*> (&_array[i]->BaseDefense), sizeof( _array[i]->BaseDefense ) );
		ofs.write( reinterpret_cast <const char*> (&_array[i]->BaseSpeed), sizeof( _array[i]->BaseSpeed ) );
		ofs.write( reinterpret_cast <const char*> (&_array[i]->BaseSpecial), sizeof( _array[i]->BaseSpecial ) );
		ofs.write( reinterpret_cast <const char*> (&_array[i]->Type1), sizeof( _array[i]->Type1 ) );
		ofs.write( reinterpret_cast <const char*> (&_array[i]->Type2), sizeof( _array[i]->Type2 ) );
		ofs.write( reinterpret_cast <const char*> (&_array[i]->CatchRate), sizeof( _array[i]->CatchRate ) );
		ofs.write( reinterpret_cast <const char*> (&_array[i]->BaseExpYield), sizeof( _array[i]->BaseExpYield ) );
		ofs.write( reinterpret_cast <const char*> (&_array[i]->Move1), sizeof( _array[i]->Move1 ) );
		ofs.write( reinterpret_cast <const char*> (&_array[i]->Move2), sizeof( _array[i]->Move2 ) );
		ofs.write( reinterpret_cast <const char*> (&_array[i]->Move3), sizeof( _array[i]->Move3 ) );
		ofs.write( reinterpret_cast <const char*> (&_array[i]->Move4), sizeof( _array[i]->Move4 ) );
		ofs.write( reinterpret_cast <const char*> (&_array[i]->GrowthRate), sizeof( _array[i]->GrowthRate ) );
	};
	ofs.close();
	return;
};