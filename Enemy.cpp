#include "Enemy.h"
#include "TextureManager.h"
#include "Constants.h"

Enemy::Enemy(const char* textureSheet, SDL_Renderer* ren, int x, int y) {
	renderer = ren;
	texture = TextureManager::LoadTexture(textureSheet, ren);

	// Init position
	PosX = x;
	PosY = y;
}

Enemy::~Enemy() {
	SDL_DestroyTexture(texture);
}

// Update enemy position
void Enemy::Update(int camX, int camY) {
	entityRect.w = ENTITY_SIZE * 2;
	entityRect.h = ENTITY_SIZE * 2;
	entityRect.x = PosX - camX;
	entityRect.y = PosY - camY;
}

int Enemy::getPosX() {
	return PosX;
}

int Enemy::getPosY() {
	return PosY;
}

void Enemy::Render() {
	SDL_RenderCopy(renderer, texture, NULL, &entityRect);
}