#pragma once

#include <string>
#include <iostream>
#include <fstream>

class Language_Master
{

public:
	static std::string Language_Master::LANGUAGE;

	static std::string Language_Master::USED;
	static std::string Language_Master::THEY_MISSED;
	static std::string Language_Master::YOU_MISSED;
	static std::string Language_Master::FAINTED;
	static std::string Language_Master::YOU_WIN;
	static std::string Language_Master::OPENING_STRING;
	static std::string Language_Master::VICTORY_TEXT;
	
	static std::string Language_Master::AGATHA_TEXT;
	static std::string Language_Master::BRUNO_TEXT;
	static std::string Language_Master::LORELEI_TEXT;

	static std::string Language_Master::CANNOT_RUN;

	static std::string Language_Master::FAILURE_TEXT;
	
	static int Init(std::string _language);

	static char* StringToCString(std::string);
};