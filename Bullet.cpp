#include "Bullet.h"
#include "TextureManager.h"
#include "Constants.h"

Bullet::Bullet(const char* textureSheet, SDL_Renderer* ren, int x, int y) {
	renderer = ren;
	texture = TextureManager::LoadTexture(textureSheet, ren);

	// Init position
	PosX = x;
	PosY = y;
}

Bullet::~Bullet() {
	SDL_DestroyTexture(texture);
}

// Update Bullet position
void Bullet::Update(int camX, int camY) {
	entityRect.w = ENTITY_SIZE * 2;
	entityRect.h = ENTITY_SIZE * 2;
	entityRect.x = PosX - camX;
	entityRect.y = PosY - camY;
}

void Bullet::Move(int VelX, int VelY) {
	// Move the bullet left or right
	PosX += VelX;

	// Move the bullet up or down
	PosY += VelY;
}

void Bullet::Render() {
	SDL_RenderCopy(renderer, texture, NULL, &entityRect);
}