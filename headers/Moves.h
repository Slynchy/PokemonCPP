#include <string>

#ifndef MOVES_H
#define MOVES_H

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

/*
	db \1 ; animation (interchangeable with move id)
	db \2 ; effect
	db \3 ; power
	db \4 ; type
	db \5 percent ; accuracy
	db \6 ; pp
*/
struct Move 
{
	unsigned char ID;
	unsigned char Effect;
	unsigned char Power;
	unsigned char Type;
	unsigned char Accuracy; // percent
	unsigned char PP;
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
	PSYCHIC_M    ,
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
	"SING_m",
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
	"PSYCHIC_M" ,
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

enum MOVE_EFFECTS {
	NO_ADDITIONAL_EFFECT,// $00
	UNUSED_EFFECT_01,    // $01
	POISON_SIDE_EFFECT1, // $02
	DRAIN_HP_EFFECT,     // $03
	BURN_SIDE_EFFECT1,   // $04
	FREEZE_SIDE_EFFECT,  // $05
	PARALYZE_SIDE_EFFECT1,      // $06
	EXPLODE_EFFECT,      // $07 Explosion, Self Destruct
	DREAM_EATER_EFFECT,  // $08
	MIRROR_MOVE_EFFECT,  // $09
	ATTACK_UP1_EFFECT,   // $0A
	DEFENSE_UP1_EFFECT,  // $0B
	SPEED_UP1_EFFECT,    // $0C
	SPECIAL_UP1_EFFECT,  // $0D
	ACCURACY_UP1_EFFECT, // $0E
	EVASION_UP1_EFFECT,  // $0F
	PAY_DAY_EFFECT,      // $10
	SWIFT_EFFECT, // $11
	ATTACK_DOWN1_EFFECT, // $12
	DEFENSE_DOWN1_EFFECT,// $13
	SPEED_DOWN1_EFFECT,  // $14
	SPECIAL_DOWN1_EFFECT,// $15
	ACCURACY_DOWN1_EFFECT,// $16
	EVASION_DOWN1_EFFECT,// $17
	CONVERSION_EFFECT,   // $18
	HAZE_EFFECT,  // $19
	BIDE_EFFECT,  // $1A
	THRASH_PETAL_DANCE_EFFECT,  // $1B
	SWITCH_AND_TELEPORT_EFFECT, // $1C
	TWO_TO_FIVE_ATTACKS_EFFECT, // $1D
	UNUSED_EFFECT_1E,    // $1E
	FLINCH_SIDE_EFFECT1, // $1F
	SLEEP_EFFECT, // $20
	POISON_SIDE_EFFECT2, // $21
	BURN_SIDE_EFFECT2,   // $22
	UNUSED_EFFECT_23,    // $23
	PARALYZE_SIDE_EFFECT2,// $24
	FLINCH_SIDE_EFFECT2, // $25
	OHKO_EFFECT,  // $26 moves like Horn Drill
	CHARGE_EFFECT,// $27 moves like Solar Beam
	SUPER_FANG_EFFECT,   // $28
	SPECIAL_DAMAGE_EFFECT,// $29 Seismic Toss, Night Shade, Sonic Boom, Dragon Rage, Psywave
	TRAPPING_EFFECT,     // $2A moves like Wrap
	FLY_EFFECT,   // $2B
	ATTACK_TWICE_EFFECT, // $2C
	JUMP_KICK_EFFECT,    // $2D Jump Kick and Hi Jump Kick effect
	MIST_EFFECT,  // $2E
	FOCUS_ENERGY_EFFECT, // $2F
	RECOIL_EFFECT,// $30 moves like Double Edge
	CONFUSION_EFFECT,    // $31 Confuse Ray, Supersonic (not the move Confusion)
	ATTACK_UP2_EFFECT,   // $32
	DEFENSE_UP2_EFFECT,  // $33
	SPEED_UP2_EFFECT,    // $34
	SPECIAL_UP2_EFFECT,  // $35
	ACCURACY_UP2_EFFECT, // $36
	EVASION_UP2_EFFECT,  // $37
	HEAL_EFFECT,  // $38 Recover, Softboiled, Rest
	TRANSFORM_EFFECT,    // $39
	ATTACK_DOWN2_EFFECT, // $3A
	DEFENSE_DOWN2_EFFECT,// $3B
	SPEED_DOWN2_EFFECT,  // $3C
	SPECIAL_DOWN2_EFFECT,// $3D
	ACCURACY_DOWN2_EFFECT,// $3E
	EVASION_DOWN2_EFFECT,// $3F
	LIGHT_SCREEN_EFFECT, // $40
	REFLECT_EFFECT,// $41
	POISON_EFFECT,// $42
	PARALYZE_EFFECT,     // $43
	ATTACK_DOWN_SIDE_EFFECT,    // $44
	DEFENSE_DOWN_SIDE_EFFECT,   // $45
	SPEED_DOWN_SIDE_EFFECT,     // $46
	SPECIAL_DOWN_SIDE_EFFECT,   // $47
	UNUSED_EFFECT_48,    // $48
	UNUSED_EFFECT_49,    // $49
	UNUSED_EFFECT_4A,    // $4A
	UNUSED_EFFECT_4B,    // $4B
	CONFUSION_SIDE_EFFECT,// $4C
	TWINEEDLE_EFFECT,    // $4D
	UNUSED_EFFECT_4E,    // $4E
	SUBSTITUTE_EFFECT,   // $4F
	HYPER_BEAM_EFFECT,   // $50
	RAGE_EFFECT,  // $51
	MIMIC_EFFECT, // $52
	METRONOME_EFFECT,    // $53
	LEECH_SEED_EFFECT,   // $54
	SPLASH_EFFECT,// $55
	DISABLE_EFFECT// $56
};

const Move MOVES_ARRAY[165] = {
{POUND,        NO_ADDITIONAL_EFFECT,        40, NORMAL,   100, 35},
{KARATE_CHOP,  NO_ADDITIONAL_EFFECT,        50, NORMAL,   100, 25},
{DOUBLESLAP,   TWO_TO_FIVE_ATTACKS_EFFECT,  15, NORMAL,    85, 10},
{COMET_PUNCH,  TWO_TO_FIVE_ATTACKS_EFFECT,  18, NORMAL,    85, 15},
{MEGA_PUNCH,   NO_ADDITIONAL_EFFECT,        80, NORMAL,    85, 20},
{PAY_DAY,      PAY_DAY_EFFECT,              40, NORMAL,   100, 20},
{FIRE_PUNCH,   BURN_SIDE_EFFECT1,           75, FIRE,     100, 15},
{ICE_PUNCH,    FREEZE_SIDE_EFFECT,          75, ICE,      100, 15},
{THUNDERPUNCH, PARALYZE_SIDE_EFFECT1,       75, ELECTRIC, 100, 15},
{SCRATCH,      NO_ADDITIONAL_EFFECT,        40, NORMAL,   100, 35},
{VICEGRIP,     NO_ADDITIONAL_EFFECT,        55, NORMAL,   100, 30},
{GUILLOTINE,   OHKO_EFFECT,                  1, NORMAL,    30,  5},
{RAZOR_WIND,   CHARGE_EFFECT,               80, NORMAL,    75, 10},
{SWORDS_DANCE, ATTACK_UP2_EFFECT,            0, NORMAL,   100, 30},
{CUT,          NO_ADDITIONAL_EFFECT,        50, NORMAL,    95, 30},
{GUST,         NO_ADDITIONAL_EFFECT,        40, NORMAL,   100, 35},
{WING_ATTACK,  NO_ADDITIONAL_EFFECT,        35, FLYING,   100, 35},
{WHIRLWIND,    SWITCH_AND_TELEPORT_EFFECT,   0, NORMAL,    85, 20},
{FLY,          FLY_EFFECT,                  70, FLYING,    95, 15},
{BIND,         TRAPPING_EFFECT,             15, NORMAL,    75, 20},
{SLAM,         NO_ADDITIONAL_EFFECT,        80, NORMAL,    75, 20},
{VINE_WHIP,    NO_ADDITIONAL_EFFECT,        35, GRASS,    100, 10},
{STOMP,        FLINCH_SIDE_EFFECT2,         65, NORMAL,   100, 20},
{DOUBLE_KICK,  ATTACK_TWICE_EFFECT,         30, FIGHTING, 100, 30},
{MEGA_KICK,    NO_ADDITIONAL_EFFECT,       120, NORMAL,    75,  5},
{JUMP_KICK,    JUMP_KICK_EFFECT,            70, FIGHTING,  95, 25},
{ROLLING_KICK, FLINCH_SIDE_EFFECT2,         60, FIGHTING,  85, 15},
{SAND_ATTACK,  ACCURACY_DOWN1_EFFECT,        0, NORMAL,   100, 15},
{HEADBUTT,     FLINCH_SIDE_EFFECT2,         70, NORMAL,   100, 15},
{HORN_ATTACK,  NO_ADDITIONAL_EFFECT,        65, NORMAL,   100, 25},
{FURY_ATTACK,  TWO_TO_FIVE_ATTACKS_EFFECT,  15, NORMAL,    85, 20},
{HORN_DRILL,   OHKO_EFFECT,                  1, NORMAL,    30,  5},
{TACKLE,       NO_ADDITIONAL_EFFECT,        35, NORMAL,    95, 35},
{BODY_SLAM,    PARALYZE_SIDE_EFFECT2,       85, NORMAL,   100, 15},
{WRAP,         TRAPPING_EFFECT,             15, NORMAL,    85, 20},
{TAKE_DOWN,    RECOIL_EFFECT,               90, NORMAL,    85, 20},
{THRASH,       THRASH_PETAL_DANCE_EFFECT,   90, NORMAL,   100, 20},
{DOUBLE_EDGE,  RECOIL_EFFECT,              100, NORMAL,   100, 15},
{TAIL_WHIP,    DEFENSE_DOWN1_EFFECT,         0, NORMAL,   100, 30},
{POISON_STING, POISON_SIDE_EFFECT1,         15, POISON,   100, 35},
{TWINEEDLE,    TWINEEDLE_EFFECT,            25, BUG,      100, 20},
{PIN_MISSILE,  TWO_TO_FIVE_ATTACKS_EFFECT,  14, BUG,       85, 20},
{LEER,         DEFENSE_DOWN1_EFFECT,         0, NORMAL,   100, 30},
{BITE,         FLINCH_SIDE_EFFECT1,         60, NORMAL,   100, 25},
{GROWL,        ATTACK_DOWN1_EFFECT,          0, NORMAL,   100, 40},
{ROAR,         SWITCH_AND_TELEPORT_EFFECT,   0, NORMAL,   100, 20},
{SING_m,         SLEEP_EFFECT,                 0, NORMAL,    55, 15},
{SUPERSONIC,   CONFUSION_EFFECT,             0, NORMAL,    55, 20},
{SONICBOOM,    SPECIAL_DAMAGE_EFFECT,        1, NORMAL,    90, 20},
{DISABLE,      DISABLE_EFFECT,               0, NORMAL,    55, 20},
{ACID,         DEFENSE_DOWN_SIDE_EFFECT,    40, POISON,   100, 30},
{EMBER,        BURN_SIDE_EFFECT1,           40, FIRE,     100, 25},
{FLAMETHROWER, BURN_SIDE_EFFECT1,           95, FIRE,     100, 15},
{MIST,         MIST_EFFECT,                  0, ICE,      100, 30},
{WATER_GUN,    NO_ADDITIONAL_EFFECT,        40, WATER,    100, 25},
{HYDRO_PUMP,   NO_ADDITIONAL_EFFECT,       120, WATER,     80,  5},
{SURF,         NO_ADDITIONAL_EFFECT,        95, WATER,    100, 15},
{ICE_BEAM,     FREEZE_SIDE_EFFECT,          95, ICE,      100, 10},
{BLIZZARD,     FREEZE_SIDE_EFFECT,         120, ICE,       90,  5},
{PSYBEAM,      CONFUSION_SIDE_EFFECT,       65, PSYCHIC,  100, 20},
{BUBBLEBEAM,   SPEED_DOWN_SIDE_EFFECT,      65, WATER,    100, 20},
{AURORA_BEAM,  ATTACK_DOWN_SIDE_EFFECT,     65, ICE,      100, 20},
{HYPER_BEAM,   HYPER_BEAM_EFFECT,          150, NORMAL,    90,  5},
{PECK,         NO_ADDITIONAL_EFFECT,        35, FLYING,   100, 35},
{DRILL_PECK,   NO_ADDITIONAL_EFFECT,        80, FLYING,   100, 20},
{SUBMISSION,   RECOIL_EFFECT,               80, FIGHTING,  80, 25},
{LOW_KICK,     FLINCH_SIDE_EFFECT2,         50, FIGHTING,  90, 20},
{COUNTER,      NO_ADDITIONAL_EFFECT,         1, FIGHTING, 100, 20},
{SEISMIC_TOSS, SPECIAL_DAMAGE_EFFECT,        1, FIGHTING, 100, 20},
{STRENGTH,     NO_ADDITIONAL_EFFECT,        80, NORMAL,   100, 15},
{ABSORB,       DRAIN_HP_EFFECT,             20, GRASS,    100, 20},
{MEGA_DRAIN,   DRAIN_HP_EFFECT,             40, GRASS,    100, 10},
{LEECH_SEED,   LEECH_SEED_EFFECT,            0, GRASS,     90, 10},
{GROWTH,       SPECIAL_UP1_EFFECT,           0, NORMAL,   100, 40},
{RAZOR_LEAF,   NO_ADDITIONAL_EFFECT,        55, GRASS,     95, 25},
{SOLARBEAM,    CHARGE_EFFECT,              120, GRASS,    100, 10},
{POISONPOWDER, POISON_EFFECT,                0, POISON,    75, 35},
{STUN_SPORE,   PARALYZE_EFFECT,              0, GRASS,     75, 30},
{SLEEP_POWDER, SLEEP_EFFECT,                 0, GRASS,     75, 15},
{PETAL_DANCE,  THRASH_PETAL_DANCE_EFFECT,   70, GRASS,    100, 20},
{STRING_SHOT,  SPEED_DOWN1_EFFECT,           0, BUG,       95, 40},
{DRAGON_RAGE,  SPECIAL_DAMAGE_EFFECT,        1, DRAGON,   100, 10},
{FIRE_SPIN,    TRAPPING_EFFECT,             15, FIRE,      70, 15},
{THUNDERSHOCK, PARALYZE_SIDE_EFFECT1,       40, ELECTRIC, 100, 30},
{THUNDERBOLT,  PARALYZE_SIDE_EFFECT1,       95, ELECTRIC, 100, 15},
{THUNDER_WAVE, PARALYZE_EFFECT,              0, ELECTRIC, 100, 20},
{THUNDER,      PARALYZE_SIDE_EFFECT1,      120, ELECTRIC,  70, 10},
{ROCK_THROW,   NO_ADDITIONAL_EFFECT,        50, ROCK,      65, 15},
{EARTHQUAKE,   NO_ADDITIONAL_EFFECT,       100, GROUND,   100, 10},
{FISSURE,      OHKO_EFFECT,                  1, GROUND,    30,  5},
{DIG,          CHARGE_EFFECT,              100, GROUND,   100, 10},
{TOXIC,        POISON_EFFECT,                0, POISON,    85, 10},
{CONFUSION,    CONFUSION_SIDE_EFFECT,       50, PSYCHIC,  100, 25},
{PSYCHIC_M,    SPECIAL_DOWN_SIDE_EFFECT,    90, PSYCHIC,  100, 10},
{HYPNOSIS,     SLEEP_EFFECT,                 0, PSYCHIC,   60, 20},
{MEDITATE,     ATTACK_UP1_EFFECT,            0, PSYCHIC,  100, 40},
{AGILITY,      SPEED_UP2_EFFECT,             0, PSYCHIC,  100, 30},
{QUICK_ATTACK, NO_ADDITIONAL_EFFECT,        40, NORMAL,   100, 30},
{RAGE,         RAGE_EFFECT,                 20, NORMAL,   100, 20},
{TELEPORT,     SWITCH_AND_TELEPORT_EFFECT,   0, PSYCHIC,  100, 20},
{NIGHT_SHADE,  SPECIAL_DAMAGE_EFFECT,        0, GHOST,    100, 15},
{MIMIC,        MIMIC_EFFECT,                 0, NORMAL,   100, 10},
{SCREECH,      DEFENSE_DOWN2_EFFECT,         0, NORMAL,    85, 40},
{DOUBLE_TEAM,  EVASION_UP1_EFFECT,           0, NORMAL,   100, 15},
{RECOVER,      HEAL_EFFECT,                  0, NORMAL,   100, 20},
{HARDEN,       DEFENSE_UP1_EFFECT,           0, NORMAL,   100, 30},
{MINIMIZE,     EVASION_UP1_EFFECT,           0, NORMAL,   100, 20},
{SMOKESCREEN,  ACCURACY_DOWN1_EFFECT,        0, NORMAL,   100, 20},
{CONFUSE_RAY,  CONFUSION_EFFECT,             0, GHOST,    100, 10},
{WITHDRAW,     DEFENSE_UP1_EFFECT,           0, WATER,    100, 40},
{DEFENSE_CURL, DEFENSE_UP1_EFFECT,           0, NORMAL,   100, 40},
{BARRIER,      DEFENSE_UP2_EFFECT,           0, PSYCHIC,  100, 30},
{LIGHT_SCREEN, LIGHT_SCREEN_EFFECT,          0, PSYCHIC,  100, 30},
{HAZE,         HAZE_EFFECT,                  0, ICE,      100, 30},
{REFLECT,      REFLECT_EFFECT,               0, PSYCHIC,  100, 20},
{FOCUS_ENERGY, FOCUS_ENERGY_EFFECT,          0, NORMAL,   100, 30},
{BIDE,         BIDE_EFFECT,                  0, NORMAL,   100, 10},
{METRONOME,    METRONOME_EFFECT,             0, NORMAL,   100, 10},
{MIRROR_MOVE,  MIRROR_MOVE_EFFECT,           0, FLYING,   100, 20},
{SELFDESTRUCT, EXPLODE_EFFECT,             130, NORMAL,   100,  5},
{EGG_BOMB,     NO_ADDITIONAL_EFFECT,       100, NORMAL,    75, 10},
{LICK,         PARALYZE_SIDE_EFFECT2,       20, GHOST,    100, 30},
{SMOG,         POISON_SIDE_EFFECT2,         20, POISON,    70, 20},
{SLUDGE,       POISON_SIDE_EFFECT2,         65, POISON,   100, 20},
{BONE_CLUB,    FLINCH_SIDE_EFFECT1,         65, GROUND,    85, 20},
{FIRE_BLAST,   BURN_SIDE_EFFECT2,          120, FIRE,      85,  5},
{WATERFALL,    NO_ADDITIONAL_EFFECT,        80, WATER,    100, 15},
{CLAMP,        TRAPPING_EFFECT,             35, WATER,     75, 10},
{SWIFT,        SWIFT_EFFECT,                60, NORMAL,   100, 20},
{SKULL_BASH,   CHARGE_EFFECT,              100, NORMAL,   100, 15},
{SPIKE_CANNON, TWO_TO_FIVE_ATTACKS_EFFECT,  20, NORMAL,   100, 15},
{CONSTRICT,    SPEED_DOWN_SIDE_EFFECT,      10, NORMAL,   100, 35},
{AMNESIA,      SPECIAL_UP2_EFFECT,           0, PSYCHIC,  100, 20},
{KINESIS,      ACCURACY_DOWN1_EFFECT,        0, PSYCHIC,   80, 15},
{SOFTBOILED,   HEAL_EFFECT,                  0, NORMAL,   100, 10},
{HI_JUMP_KICK, JUMP_KICK_EFFECT,            85, FIGHTING,  90, 20},
{GLARE,        PARALYZE_EFFECT,              0, NORMAL,    75, 30},
{DREAM_EATER,  DREAM_EATER_EFFECT,         100, PSYCHIC,  100, 15},
{POISON_GAS,   POISON_EFFECT,                0, POISON,    55, 40},
{BARRAGE,      TWO_TO_FIVE_ATTACKS_EFFECT,  15, NORMAL,    85, 20},
{LEECH_LIFE,   DRAIN_HP_EFFECT,             20, BUG,      100, 15},
{LOVELY_KISS,  SLEEP_EFFECT,                 0, NORMAL,    75, 10},
{SKY_ATTACK,   CHARGE_EFFECT,              140, FLYING,    90,  5},
{TRANSFORM,    TRANSFORM_EFFECT,             0, NORMAL,   100, 10},
{BUBBLE,       SPEED_DOWN_SIDE_EFFECT,      20, WATER,    100, 30},
{DIZZY_PUNCH,  NO_ADDITIONAL_EFFECT,        70, NORMAL,   100, 10},
{SPORE,        SLEEP_EFFECT,                 0, GRASS,    100, 15},
{FLASH,        ACCURACY_DOWN1_EFFECT,        0, NORMAL,    70, 20},
{PSYWAVE,      SPECIAL_DAMAGE_EFFECT,        1, PSYCHIC,   80, 15},
{SPLASH,       SPLASH_EFFECT,                0, NORMAL,   100, 40},
{ACID_ARMOR,   DEFENSE_UP2_EFFECT,           0, POISON,   100, 40},
{CRABHAMMER,   NO_ADDITIONAL_EFFECT,        90, WATER,     85, 10},
{EXPLOSION,    EXPLODE_EFFECT,             170, NORMAL,   100,  5},
{FURY_SWIPES,  TWO_TO_FIVE_ATTACKS_EFFECT,  18, NORMAL,    80, 15},
{BONEMERANG,   ATTACK_TWICE_EFFECT,         50, GROUND,    90, 10},
{REST,         HEAL_EFFECT,                  0, PSYCHIC,  100, 10},
{ROCK_SLIDE,   NO_ADDITIONAL_EFFECT,        75, ROCK,      90, 10},
{HYPER_FANG,   FLINCH_SIDE_EFFECT1,         80, NORMAL,    90, 15},
{SHARPEN,      ATTACK_UP1_EFFECT,            0, NORMAL,   100, 30},
{CONVERSION,   CONVERSION_EFFECT,            0, NORMAL,   100, 30},
{TRI_ATTACK,   NO_ADDITIONAL_EFFECT,        80, NORMAL,   100, 10},
{SUPER_FANG,   SUPER_FANG_EFFECT,            1, NORMAL,    90, 10},
{SLASH,        NO_ADDITIONAL_EFFECT,        70, NORMAL,   100, 20},
{SUBSTITUTE,   SUBSTITUTE_EFFECT,            0, NORMAL,   100, 10},
{STRUGGLE,     RECOIL_EFFECT,               50, NORMAL,   100, 10}
};

#endif