#include "Game.hpp"

class Player {
public:
	Player(const char* textureSheet, SDL_Renderer* ren);
	~Player();

	static const int PLAYER_VEL = 10;

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
		return entityRect;
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

	SDL_Texture* texture;
	SDL_Rect entityRect;
	SDL_Renderer* renderer;
};