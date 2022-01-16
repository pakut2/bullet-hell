#include <stdio.h>
#include "Game.hpp"
#include "Constants.h"

Game* game = nullptr;

int main(int argc, char* argv[]) {
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;
	int realTime = 0;

	game = new Game();
	game->init("BulletHell", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);

	while (game->running()) {
		if (game->newGame()) {
			game->clean();
			game->init("BulletHell", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);
			realTime = 0;
			game->setNewGame();
		}

		frameStart = SDL_GetTicks();

		if (game->menu()) {
			game->handleMenuEvents();
			game->renderMenu();
		}

		if (game->gameOver()) {
			game->handleGameOverEvents();
			game->renderGameOver();
		}

		if (!game->menu() && !game->gameOver()) {
			game->handleEvents();
			game->update();
			game->render();
		}

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
			realTime += frameDelay - frameTime;
		}
		else {
			realTime += frameTime;
		}

		game->setRealTime(realTime / 1000);
	}

	game->clean();

	return 0;
}