#include "Zones.h"

void Zone::LoadObjectData(char *filename)
{
	//Init
	std::fstream fs;
	//char *tempStr = strcat(filename,".bin");
	
	// Open and test
	fs.open(filename,std::fstream::in | std::fstream::binary);
	if(!fs)
	{
		fprintf(stderr, "Couldn't load file: %s\n", SDL_GetError());
	};

	//First two parts of data is pos, then size
	fs >> Zone::world_y;
	fs >> Zone::world_x;
	fs >> Zone::y_size;
	fs >> Zone::x_size;

	//Then resize the vector based on this info
	objectData.resize(y_size);
    for(int i = 0 ; i < y_size ; ++i)
    {
    	objectData[i].resize(Zone::x_size);
    }

	//Then load data into vector
	for(int y = 0; y < y_size; y++)
	{
		for(int x = 0; x < Zone::x_size; x++)
		{
			//fs >> 
			int tempInt = 0;
			fs >> tempInt;
			objectData[y][x] = tempInt;
		};
	};

	//Close FS
	fs.close();

	// THIS IS SO INSECURE THAT IT ASKS ITS FRIENDS IF IT LOOKS GOOD.
	// ANYONE CAN JUST EDIT THE .BIN TO LOAD HOWEVER MUCH DATA THEY WANT
	// AND CAUSE A BUFFER-OVERFLOW.
};

void Zone::Init(char *imagefilename, SDL_Renderer *sdlRenderer,char *datafilename)
{
	//Init
	int x_size = 0;
	int y_size = 0;
	int world_x = 0;
	int world_y = 0;
	Zone::LoadObjectData(datafilename);
	Zone::LoadImage(imagefilename,sdlRenderer);
};


void Zone::LoadImage(char *filename, SDL_Renderer *sdlRenderer)
{
	//char *tempStr = strcat(filename,".png");
	Zone::image = IMG_LoadTexture(sdlRenderer,filename);
};

int CheckZone(std::vector<Zone>& _Zones, int _x, int _y)
{
	int retVal = 0;
	for(int i = 0; i < (unsigned char)_Zones.size(); i++)
	{
		if(	_x > _Zones[i].world_x &&
			_x < _Zones[i].world_x+_Zones[i].x_size &&
			_y > _Zones[i].world_y-1 &&
			_y < _Zones[i].world_y+_Zones[i].y_size)
		{
			retVal = i;
			break;
		} 
		else
		{
			retVal = -1;
		};
	};
	return retVal;
};