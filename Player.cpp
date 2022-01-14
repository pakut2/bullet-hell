#include "Player.h"
#include "TextureManager.h"

Player::Player(const char* textureSheet, SDL_Renderer* ren, int initialX, int initialY) {
	renderer = ren;
	objectTexture = TextureManager::LoadTexture(textureSheet, ren);

	xPos = initialX;
	yPos = initialY;

	velocity = 30;
}

void Player::Update() {
	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xPos;
	destRect.y = yPos;

	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;
}

void Player::MoveUp() {
	yPos -= velocity;
	destRect.w = 32;
	destRect.h = 32;
	destRect.y = yPos;
}

void Player::MoveDown() {
	yPos += velocity;
	destRect.w = 32;
	destRect.h = 32;
	destRect.y = yPos;
}

void Player::MoveRight() {
	xPos += velocity;
	destRect.w = 32;
	destRect.h = 32;
	destRect.x = xPos;
}

void Player::MoveLeft() {
	xPos -= velocity;
	destRect.w = 32;
	destRect.h = 32;
	destRect.x = xPos;
}

void Player::Render() {
	SDL_RenderCopy(renderer, objectTexture, NULL, &destRect);
}