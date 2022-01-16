#include "Player.h"
#include "TextureManager.h"
#include "Constants.h"

Player::Player(const char* textureSheet, SDL_Renderer* ren) {
	renderer = ren;
	texture = TextureManager::LoadTexture(textureSheet, ren);

	playerSize = 30;

	// Init position
	PosX = 0;
	PosY = 100;

	// Init velocity
	VelX = 0;
	VelY = 0;

	// Init inivicibility frames
	invincibilityFrames = 0;

	// Init player hp
	hp = PLAYER_HEALTH;

	srcRect.w = playerSize;
	srcRect.h = playerSize;
}

Player::~Player() {
	SDL_DestroyTexture(texture);
}

// Update player position
void Player::Update(int camX, int camY) {
	destRect.w = playerSize * 2;
	destRect.h = playerSize * 2;
	destRect.x = PosX - camX;
	destRect.y = PosY - camY;
}

// Handle keyboard input
void Player::HandleEvent(SDL_Event& e) {
	// Adjust the player velocity
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_UP:
			VelY -= PLAYER_VEL;
			srcRect.x = playerSize * 2;
			break;
		case SDLK_DOWN:
			VelY += PLAYER_VEL;
			srcRect.x = playerSize;
			break;
		case SDLK_LEFT:
			VelX -= PLAYER_VEL;
			srcRect.x = playerSize * 3;
			break;
		case SDLK_RIGHT:
			VelX += PLAYER_VEL;
			srcRect.x = 0;
			break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_UP:
			VelY += PLAYER_VEL;
			break;
		case SDLK_DOWN:
			VelY -= PLAYER_VEL;
			break;
		case SDLK_LEFT:
			VelX += PLAYER_VEL;
			break;
		case SDLK_RIGHT:
			VelX -= PLAYER_VEL;
			break;
		}
	}
}

void Player::Move() {
	// Move the player left or right
	PosX += VelX;

	// If the player went too far to the left or right
	if ((PosX < 0) || (PosX + ENTITY_SIZE > LEVEL_WIDTH))
	{
		PosX -= VelX;
	}

	// Move the player up or down
	PosY += VelY;

	// If the player went too far up or down
	if ((PosY < 0) || (PosY + ENTITY_SIZE > LEVEL_HEIGHT)) {
		PosY -= VelY;
	}
}

int Player::getPosX() {
	return PosX;
}

int Player::getPosY() {
	return PosY;
}

int Player::getInvincibilityFrames() {
	return invincibilityFrames;
}

int Player::getHp() {
	return hp;
}

void Player::setInvincibility(int invincibility) {
	invincibilityFrames = invincibility;
}

void Player::setHp() {
	hp--;
}

void Player::Render() {
	SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}