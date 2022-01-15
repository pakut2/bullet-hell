#pragma once
#include "Game.hpp"

class Label {
public:
	Label(const char* textureSheet, SDL_Renderer* ren, int y, int x, const char* text, bool small);
	~Label();

	void Render();

	SDL_Rect getRect() {
		return entityRect;
	}

private:
	int PosX;
	int PosY;

	SDL_Texture* texture;
	SDL_Rect entityRect;
	SDL_Renderer* renderer;
};