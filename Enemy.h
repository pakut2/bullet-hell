#pragma once
#include "Game.hpp"

class Enemy {
public:
	Enemy(const char* textureSheet, SDL_Renderer* ren, int x, int y);
	~Enemy();

	void Update(int camX, int camY);
	void Render();

	int getPosX();
	int getPosY();

private:
	int PosX, PosY;

	SDL_Texture* texture;
	SDL_Rect destRect;
	SDL_Renderer* renderer;
};