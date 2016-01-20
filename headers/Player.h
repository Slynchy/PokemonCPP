#include "SDL.h" // Main SDL library
#include <SDL_image.h> // SDL Image library
#include "../src/SDLFunctions.h"
#include "Zones.h"
#include "Keyboard.h"
#include <math.h>
#include <vector>
#include <iostream>

enum directions { RIGHT , LEFT , UP , DOWN };

struct Animation
{
	std::vector<SDL_Rect> frames;
	std::vector<SDL_RendererFlip> flip_Flag;
	void init(int f1_x, int f1_y, SDL_RendererFlip f1_flip,int f2_x, int f2_y, SDL_RendererFlip f2_flip);
	void init(int f1_x, int f1_y, SDL_RendererFlip f1_flip,int f2_x, int f2_y, SDL_RendererFlip f2_flip, int f3_x, int f3_y, SDL_RendererFlip f3_flip);
	void init(int f1_x, int f1_y, SDL_RendererFlip f1_flip,int f2_x, int f2_y, SDL_RendererFlip f2_flip, int f3_x, int f3_y, SDL_RendererFlip f3_flip, int f4_x, int f4_y, SDL_RendererFlip f4_flip);
};

class Player
{
	private:

	public:
		int m_x;
		int m_y;
		SDL_Texture *spritesheet;
		bool m_moving;
		directions direction;
		SDL_Rect standingLeftRight_SpriteRect;
		SDL_Rect standingUp_SpriteRect;
		SDL_Rect standingDown_SpriteRect;
		unsigned char animationFrame;
		unsigned char animationFrame2;
		int zoneIndex;

		Animation walkingLeftRight;
		Animation walkingUp;
		Animation walkingDown;

		void Init(SDL_Renderer *sdlRenderer);
		void KeyboardInput(Keys *keys, std::vector<Zone>& levelCollisionArray);
		void Draw(SDL_Renderer *sdlRenderer);
		bool CheckCollision(std::vector<Zone> levelCollisionArray, int x_pos, int y_pos);

};
