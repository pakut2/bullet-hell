#pragma once
#include "Game.hpp"

class Enemy {
public:
	Enemy(const char* textureSheet, SDL_Renderer* ren, int x, int y);
	~Enemy();

	void Update(int camX, int camY);
	void UpdateMoving(int camX, int camY);
	void Render();

	int getPosX();
	int getPosY();
	int getActualX();
	int getActualY();

	SDL_Rect getRect() {
		return destRect;
	}

private:
	int PosX, PosY, actualX, actualY;

	// Angle of circular enemy movement
	double angle;

	SDL_Texture* texture;
	SDL_Rect destRect;
	SDL_Renderer* renderer;
};