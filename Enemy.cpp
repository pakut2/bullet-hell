#include "Enemy.h"
#include "TextureManager.h"
#include "Constants.h"
#include <math.h>

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
	destRect.x = (PosX - camX) + (RADIUS * sin(angle));
	destRect.y = (PosY - camY) + (RADIUS * cos(angle));
	actualX = PosX + (RADIUS * sin(angle));
	actualY = PosY + (RADIUS * cos(angle));
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