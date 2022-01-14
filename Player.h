#pragma once
#include "Game.hpp"

class Player {
public:
	Player(const char* textureSheet, SDL_Renderer* ren, int x, int y);
	~Player();

	int velocity;

	void Update();
	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();
	void Render();

private:
	int xPos;
	int yPos;

	SDL_Texture* objectTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;
};