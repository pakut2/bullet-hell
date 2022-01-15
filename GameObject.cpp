#include "GameObject.h"
#include "TextureManager.h"
#include "Constants.h"

GameObject::GameObject(const char* textureSheet, SDL_Renderer* ren, int x, int y) {
	renderer = ren;
	texture = TextureManager::LoadTexture(textureSheet, ren);

	// Init position
	PosX = x;
	PosY = y;

	entityRect.w = ENTITY_SIZE * 2;
	entityRect.h = ENTITY_SIZE * 2;
	entityRect.x = PosX;
	entityRect.y = PosY;
}

GameObject::~GameObject() {
	SDL_DestroyTexture(texture);
}

void GameObject::Render() {
	SDL_RenderCopy(renderer, texture, NULL, &entityRect);
}