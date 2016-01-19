#include "SDL.h" // Main SDL library
#include <SDL_image.h> // SDL Image library
#include "../src/SDLFunctions.h"
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
		int animationFrame;
		int animationFrame2;

		Animation walkingLeftRight;
		Animation walkingUp;
		Animation walkingDown;

		void Init(SDL_Renderer *sdlRenderer);
		void KeyboardInput(const Uint8 *keyboardstate,int (&levelCollisionArray)[18][20]);
		void Draw(SDL_Renderer *sdlRenderer);
		bool CheckCollision(int (&levelCollisionArray)[18][20], int x_pos, int y_pos);

};
