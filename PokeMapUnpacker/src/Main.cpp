/// \file Main.cpp
/// \brief Unpackages CSV files from binary data
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
char * buffer;
int imageLength = 0;

int WriteObjectDataBinary(std::string);

class Zone
{
	private:
	public:
		int x_size;
		int y_size;
		int world_x;
		int world_y;
		int imgLen;
		char * image;
		std::vector< std::vector<int> > objectData;
		void LoadObjectData(const char *filename);
};

int main(int argc, char* argv[])
{
	std::cout << "PokeMapUnPacker (C) Amduat Games, Sam Lynch" << std::endl;
    if (argc < 2) {
        std::cerr << "Usage: PokeMapUnPacker.exe [.pokemap path]" << std::endl;
        return 1;
    };
	std::string filename = (std::string)argv[1];

	Zone *zone_obj = new Zone();

	zone_obj->LoadObjectData(filename.c_str());

	std::ofstream ofs;
	std::string tempStr;

	tempStr += std::to_string(zone_obj->world_y);
	tempStr += ",";
	tempStr += std::to_string(zone_obj->world_x);
	tempStr += ",";
	tempStr += std::to_string(zone_obj->y_size);
	tempStr += ",";
	tempStr += std::to_string(zone_obj->x_size);
	tempStr += ",";

	for(size_t y = 0; y < zone_obj->objectData.size(); y++)
	{
		for(size_t x = 0; x < zone_obj->objectData[0].size(); x++)
		{
			tempStr+= std::to_string((int)zone_obj->objectData[y][x]);
			tempStr+= ",";
		};
		tempStr+= "\n";
	};
	ofs.open(filename+".csv");
	ofs << tempStr;
	ofs.close();
	_getch();
	return 0;
};

int WriteObjectDataBinary(std::string filepathname)
{
	size_t lastindex = filepathname.find_last_of("."); 
	filepathname = filepathname.substr(0, lastindex); 
	std::ofstream ofs (filepathname+".pokemap", std::fstream::binary);
	// image filesize first
	ofs.write( reinterpret_cast <const char*> (&imageLength), sizeof( imageLength ) );
	// image now
	ofs.write( buffer, imageLength );

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


void Zone::LoadObjectData(const char *filename)
{
	//Init 
	int len = 0;
	int imgLen = 0;
	short int world_y;
	short int world_x;
	short int world_y_size;
	short int world_x_size;

	//Load file
	std::ifstream ifs(filename,std::ios::binary);

	//Check if file loaded...
	if(ifs)
	{
		// Get length
		ifs.seekg (0, ifs.end);
		len = ifs.tellg();
		ifs.seekg (0, ifs.beg);

		// Read world coords and size
		ifs.read((char*)&world_y, sizeof(world_y));
		ifs.read((char*)&world_x, sizeof(world_x));
		ifs.read((char*)&world_y_size, sizeof(world_y_size));
		ifs.read((char*)&world_x_size, sizeof(world_x_size));
		this->world_y = world_y;
		this->world_x = world_x;
		this->y_size = world_y_size;
		this->x_size = world_x_size;

		//Check size
		/*if(((world_y_size * world_x_size) * sizeof(world_x_size)) + (4*sizeof(world_x_size)) != (len))
		{
			std::cerr << "Filesize of " << filename << " does not match expected size! Shutting down Zone::LoadObjectData..." << std::endl;
			ifs.close();
			return;
		};*/

		//Then resize the vector based on this info
		this->objectData.resize(world_y_size);
		for(int i = 0 ; i < world_y_size ; ++i)
		{
    		this->objectData[i].resize(world_x_size);
		}

		//Then load data into vector
		for(int y = 0; y < world_y_size; y++)
		{
			for(int x = 0; x < world_x_size; x++)
			{
				// Read into int and write int to memory
				short int tempInt = 0;
				ifs.read((char*)&tempInt, sizeof(tempInt));
				this->objectData[y][x] = tempInt;
			};
		};
		ifs.read((char*)&imgLen, sizeof(imgLen));
		this->imgLen = imgLen;

		// Load Image
		this->image = new char [imgLen];
		ifs.read (this->image,imgLen);
		//this->image = IMG_LoadTexture(sdlRenderer, buffer);

		//delete buffer;

		ifs.close();
	}
	else 
	{
		std::cerr << "Failed to load " << filename << " @ Zone::LoadObjectData" << std::endl;
		return;
	};

};