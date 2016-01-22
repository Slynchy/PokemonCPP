#include "SDL.h" // Main SDL 
#include <SDL_image.h> // SDL Image library
#include <vector> 
#include <fstream> 
#include <string> 

#ifndef ZONES_H
#define ZONES_H

struct Objects
{
	std::string name;
	bool collisions;
	void Init()
	{
		name = "Undefined";
		collisions = false;
	};
	void Init(std::string _name, bool _collision)
	{
		name = _name;
		collisions = _collision;
	};
};

class Zone
{
	private:
	public:
		int x_size;
		int y_size;
		int world_x;
		int world_y;
		SDL_Texture *image;
		SDL_Texture *foreground;
		std::vector< std::vector<int> > objectData;
		void Init(char *imagefilename, SDL_Renderer *sdlRenderer,char *datafilename);
		void LoadObjectData(char *filename);
		void LoadImage(char *filename, SDL_Renderer *sdlRenderer);
};

int CheckZone(std::vector<Zone>& _Zones, int _x, int _y);

#endif