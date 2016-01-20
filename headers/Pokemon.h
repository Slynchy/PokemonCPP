
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
struct Pokemon
{
	unsigned char Index;
	short int CurrHP;
	unsigned char LevelPC;
	unsigned char StatusCond;
	unsigned char Type1;
	unsigned char Type2;
	unsigned char CatchRate_HeldItem;
	unsigned char Move1_index;
	unsigned char Move2_index;
	unsigned char Move3_index;
	unsigned char Move4_index;
	signed short int OrigTrainerID; //4 bytes instead of 3...
	signed int ExperiencePoints;
	signed short int HP_EV;
	signed short int ATTACK_EV;
	signed short int DEFENCE_EV;
	signed short int SPEED_EV;
	signed short int SPECIAL_EV;
	signed short int IVdata;
	unsigned char Move1_PP;
	unsigned char Move2_PP;
	unsigned char Move3_PP;
	unsigned char Move4_PP;
	unsigned char Level;
	short int MaxHP;
	signed short int Attack;
	signed short int Defence;
	signed short int Speed;
	signed short int Special;
};