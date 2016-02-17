#include "Zones.h"

void Zone::LoadObjectData(char *filename)
{
	//Init 
	int len = 0;
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
		if(((world_y_size * world_x_size) * sizeof(world_x_size)) + (4*sizeof(world_x_size)) != len)
		{
			std::cerr << "Filesize of " << filename << " does not match expected size! Shutting down Zone::LoadObjectData..." << std::endl;
			ifs.close();
			return;
		};

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

		ifs.close();
	}
	else 
	{
		std::cerr << "Failed to load " << filename << " @ Zone::LoadObjectData" << std::endl;
		return;
	};

};

void Zone::LoadObjectData_old(char *filename)
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