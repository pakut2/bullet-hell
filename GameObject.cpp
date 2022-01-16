#include "GameObject.h"
#include "TextureManager.h"
#include "Constants.h"

GameObject::GameObject(const char* textureSheet, SDL_Renderer* ren, int x, int y) {
	renderer = ren;
	texture = TextureManager::LoadTexture(textureSheet, ren);

	// Init position
	PosX = x;
	PosY = y;

	destRect.w = ENTITY_SIZE * 2;
	destRect.h = ENTITY_SIZE * 2;
	destRect.x = PosX;
	destRect.y = PosY;
}

GameObject::~GameObject() {
	SDL_DestroyTexture(texture);
}

void GameObject::Render() {
	SDL_RenderCopy(renderer, texture, NULL, &destRect);
}