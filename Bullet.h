#include "Game.hpp"
#include "Enemy.h"

class Bullet {
public:
	Bullet(const char* textureSheet, SDL_Renderer* ren, int x, int y);
	~Bullet();

	static const int BULLET_VEL = 10;

	void Update(int camX, int camY);
	void Move(int VelX, int VelY);
	void Render();

	SDL_Rect getRect() {
		return entityRect;
	}

	// int getPosX();
	// int getPosY();

private:
	// The current position of the bullet
	int PosX, PosY;

	// The velocity of the bullet
	int VelX, VelY;

	SDL_Texture* texture;
	SDL_Rect entityRect;
	SDL_Renderer* renderer;
};