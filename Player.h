#include "Game.hpp"

class Player {
public:
	Player(const char* textureSheet, SDL_Renderer* ren);
	~Player();

	void Update(int camX, int camY);
	void HandleEvent(SDL_Event& e);
	void Move();
	void Render();

	int getPosX();
	int getPosY();
	int getInvincibilityFrames();
	int getHp();
	void setInvincibility(int invincibility);
	void setHp();

	SDL_Rect getRect() {
		return destRect;
	}

private:
	// The current position of the player
	int PosX, PosY;

	// The velocity of the player
	int VelX, VelY;

	// Number of frames the player cannot be hit
	int invincibilityFrames;

	// Remaining health of the player
	int hp;

	// Player dimensions in a single animation state
	int playerSize;

	// Animation frame
	int animationFrame;

	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;
};