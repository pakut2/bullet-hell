#include "Game.hpp"
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"

Player* player;

Game::Game() {}
Game::~Game() {}

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen) {

	int flags = 0;

	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}

	player = new Player("assets/eti.bmp", renderer, 100, 100);
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			isRunning = false;
		}
		else if (event.key.keysym.sym == SDLK_UP) {
			player->MoveUp();
		}
		else if (event.key.keysym.sym == SDLK_DOWN) {
			player->MoveDown();
		}
		else if (event.key.keysym.sym == SDLK_RIGHT) {
			player->MoveRight();
		}
		else if (event.key.keysym.sym == SDLK_LEFT) {
			player->MoveLeft();
		}
		break;
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

void Game::update() {
	counter++;

	player->Update();

	// std::cout << counter << "\n";
}

void Game::render() {
	SDL_RenderClear(renderer);
	player->Render();
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}