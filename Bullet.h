#include "Game.hpp"
#include "Enemy.h"

class Bullet {
public:
	Bullet(const char* textureSheet, SDL_Renderer* ren, int x, int y);
	~Bullet();

	void Update(int camX, int camY);
	void Move(int VelX, int VelY);
	void Render();

	SDL_Rect getRect() {
		return destRect;
	}

private:
	// The initial position of the bullet
	int PosX, PosY;

	// The velocity of the bullet
	int VelX, VelY;

	SDL_Texture* texture;
	SDL_Rect destRect;
	SDL_Renderer* renderer;
};