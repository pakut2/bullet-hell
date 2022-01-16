#ifndef Game_hpp
#define Game_hpp

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);

	void handleEvents();
	void handleMenuEvents();
	void handleGameOverEvents();
	void update();
	void render();
	void renderMenu();
	void renderGameOver();
	void clean();

	bool running() {
		return isRunning;
	}

	bool newGame() {
		return isNewGame;
	}

	bool gameOver() {
		return isGameOver;
	}

	bool menu() {
		return isMenuActive;
	}

	void setNewGame() {
		isMenuActive = false;
		isNewGame = false;
	}

	void setRealTime(int time) {
		realTime = time;
	}

	void setDeltaTime(int time) {
		deltaTime = time;
	}

private:
	int counter, realTime, deltaTime;
	bool isRunning, isNewGame, isGameOver, isMenuActive;
	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif /* Game_hpp */