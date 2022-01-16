#include "Enemy.h"
#include "TextureManager.h"
#include "Constants.h"

Enemy::Enemy(const char* textureSheet, SDL_Renderer* ren, int x, int y) {
	renderer = ren;
	texture = TextureManager::LoadTexture(textureSheet, ren);

	// Init position
	PosX = x;
	PosY = y;
	actualX = x;
	actualY = y;
	angle = 0;
}

Enemy::~Enemy() {
	SDL_DestroyTexture(texture);
}

// Update enemy position
void Enemy::Update(int camX, int camY) {
	destRect.w = ENTITY_SIZE * 2;
	destRect.h = ENTITY_SIZE * 2;
	destRect.x = PosX - camX;
	destRect.y = PosY - camY;
}

// Update circular moving enemy position
void Enemy::UpdateMoving(int camX, int camY) {
	angle += 0.05;
	destRect.w = ENTITY_SIZE * 2;
	destRect.h = ENTITY_SIZE * 2;
	destRect.x = (PosX - camX) + (ENEMY_RADIUS * sin(angle));
	destRect.y = (PosY - camY) + (ENEMY_RADIUS * cos(angle));
	actualX = PosX + (ENEMY_RADIUS * sin(angle));
	actualY = PosY + (ENEMY_RADIUS * cos(angle));
}

int Enemy::getPosX() {
	return PosX;
}

int Enemy::getPosY() {
	return PosY;
}

int Enemy::getActualX() {
	return actualX;
}

int Enemy::getActualY() {
	return actualY;
}

void Enemy::Render() {
	SDL_RenderCopy(renderer, texture, NULL, &destRect);
}