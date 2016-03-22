/// \file Main.cpp
/// \brief Packages CSV files into binary data
/// \author Sam Lynch

#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

short int world_y;
short int world_x;
short int y_size;
short int x_size;
std::vector<std::vector<short int>> objectData;
std::string buffer;
int imageLength = 0;

int WriteObjectDataBinary(std::string);

int main(int argc, char* argv[])
{
	std::cout << "PokeMapPacker (C) Amduat Games, Sam Lynch" << std::endl;
    if (argc < 2) {
        std::cerr << "Usage: PokeMapPacker.exe [file.csv]" << std::endl;
        return 1;
    };

	//Init
	std::string filename = (std::string)argv[1];
	int counter = 0;
	
	// Open and test
	std::ifstream fs(filename);
	std::string str((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());
    std::stringstream ss(str);
	fs.close();

	//Buffer
	short int i;
	std::vector<short int> tempVect;
    while (ss >> i)
    {
        tempVect.push_back(i);

        if (ss.peek() == ',')
            ss.ignore();
        if (ss.peek() == '\n')
            ss.ignore();
    }

	//First two parts of data is pos, then size
	world_y = tempVect[counter++];
	world_x = tempVect[counter++];
	y_size = tempVect[counter++];
	x_size = tempVect[counter++];

	//Then resize the vector based on this info
	objectData.resize(y_size);
    for(int i = 0 ; i < y_size ; ++i)
    {
    	objectData[i].resize(x_size);
    }

	//Then load data into vector
	for(int y = 0; y < y_size; y++)
	{
		std::cout << std::endl;
		for(int x = 0; x < x_size; x++)
		{
			int tempInt = 0;
			tempInt = tempVect[counter++];
			objectData[y][x] = tempInt;
			std::cout << objectData[y][x] << ", ";
		};
	};
	
	size_t lastindex = filename.find_last_of("."); 
	filename = filename.substr(0, lastindex); 

	WriteObjectDataBinary(filename);
	return 0;
};

int WriteObjectDataBinary(std::string filepathname)
{
	size_t lastindex = filepathname.find_last_of("."); 
	filepathname = filepathname.substr(0, lastindex); 
	std::ofstream ofs (filepathname+".pokemap", std::fstream::binary);

	ofs.write( reinterpret_cast <const char*> (&world_y), sizeof( world_y ) );
	ofs.write( reinterpret_cast <const char*> (&world_x), sizeof( world_x ) );
	ofs.write( reinterpret_cast <const char*> (&y_size), sizeof( y_size ) );
	ofs.write( reinterpret_cast <const char*> (&x_size), sizeof( x_size ) );
	for(int y = 0; y < (int)y_size; y++)
	{
		for(int x = 0; x < (int)x_size; x++)
		{
			ofs.write( reinterpret_cast <const char*> (&objectData[y][x]), sizeof( objectData[y][x] ) );
		};
	};
	ofs.close();
	return 0;
};