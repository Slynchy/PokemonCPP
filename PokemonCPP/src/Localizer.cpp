#include "Localizer.h"

std::string Language_Master::LANGUAGE = "english";

std::string Language_Master::USED;
std::string Language_Master::THEY_MISSED;
std::string Language_Master::YOU_MISSED;
std::string Language_Master::FAINTED;
std::string Language_Master::YOU_WIN;
std::string Language_Master::OPENING_STRING;
std::string Language_Master::VICTORY_TEXT;
	
std::string Language_Master::AGATHA_TEXT;
std::string Language_Master::BRUNO_TEXT;
std::string Language_Master::LORELEI_TEXT;

std::string Language_Master::CANNOT_RUN;

std::string Language_Master::FAILURE_TEXT;

int Language_Master::Init(std::string _language)
{
	// ./localizations/english/english.txt
	std::string path = "./localizations/" + _language + "/" + _language + ".txt";
	std::ifstream ifs(path);
	if(ifs)
	{
		getline(ifs, Language_Master::USED);
		getline(ifs, Language_Master::THEY_MISSED);
		getline(ifs, Language_Master::YOU_MISSED);
		getline(ifs, Language_Master::FAINTED);
		getline(ifs, Language_Master::YOU_WIN);
		getline(ifs, Language_Master::OPENING_STRING);
		getline(ifs, Language_Master::VICTORY_TEXT);
		getline(ifs, Language_Master::AGATHA_TEXT);
		getline(ifs, Language_Master::BRUNO_TEXT);
		getline(ifs, Language_Master::LORELEI_TEXT);
		getline(ifs, Language_Master::CANNOT_RUN);
		getline(ifs, Language_Master::FAILURE_TEXT);
		ifs.close();
	} 
	else 
	{
		std::cerr << "Failed to load " << path << std::endl;
		return -1;	
	};

	return 0;
};

char* Language_Master::StringToCString(std::string _string)
{
	return _strdup(_string.c_str());
};