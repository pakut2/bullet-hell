#include "Game.hpp"
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Texture.h"
#include "Constants.h"
#include "utils.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Label.h"

Player* player;
Enemy* basicEnemies[NUMBER_OF_BASIC_ENEMIES];
Enemy* movingEnemy;
Bullet* basicEnemyBullets[NUMBER_OF_ALL_BULLETS];
Bullet* movingEnemyBullets[DIRECTIONS];
GameObject* health[PLAYER_HEALTH];

SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

Texture* BGTexture;
Texture* MenuBGTexture;
Label* startButton;
Label* exitButton;
Label* gameOverButton;
Label* menuButton;
Label* timer;

Game::Game() {}

Game::~Game() {
	clean();
}

// Init SDL
void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen) {
	isGameOver = false;
	isMenuActive = true;
	int flags = 0;

	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (!SDL_Init(SDL_INIT_EVERYTHING)) {
		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}

	BGTexture = new Texture(renderer);
	BGTexture->LoadFromFile("assets/bg.bmp");

	MenuBGTexture = new Texture(renderer);
	MenuBGTexture->LoadFromFile("assets/menubg.bmp");

	startButton = new Label("assets/start.bmp", renderer, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 2 - 120, "", false);
	exitButton = new Label("assets/exit.bmp", renderer, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 2 + 60, "", false);
	gameOverButton = new Label("assets/over.bmp", renderer, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 2 - 120, "", false);
	menuButton = new Label("assets/menu.bmp", renderer, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 2 + 60, "", false);

	for (int i = 0; i < NUMBER_OF_BASIC_ENEMIES; i++) {
		int randomX = random(0, LEVEL_WIDTH);
		int randomY = random(0, LEVEL_HEIGHT);

		basicEnemies[i] = new Enemy("assets/enemy.bmp", renderer, randomX, randomY);

		for (int j = i * NUMBER_OF_BULLETS; j < (i * NUMBER_OF_BULLETS) + NUMBER_OF_BULLETS; j++) {
			basicEnemyBullets[j] = new Bullet("assets/bullet.bmp", renderer, randomX, randomY);
		}
	}

	movingEnemy = new Enemy("assets/enemy.bmp", renderer, LEVEL_WIDTH / 2, LEVEL_HEIGHT / 2);

	for (int i = 0; i < DIRECTIONS; i++) {
		movingEnemyBullets[i] = new Bullet("assets/bullet.bmp", renderer, LEVEL_WIDTH / 2, (LEVEL_HEIGHT / 2) + RADIUS);
	}

	for (int i = 0; i < PLAYER_HEALTH; i++) {
		health[i] = new GameObject("assets/hp.bmp", renderer, i * ENTITY_SIZE * 2, 0);
	}

	player = new Player("assets/player.bmp", renderer);
}

// Handle keyboard input in game
void Game::handleEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				isRunning = false;
			}

			if (event.key.keysym.sym == SDLK_n) {
				isNewGame = true;
			}
			break;
		default:
			break;
		}
		// Handle input for the player
		player->HandleEvent(event);
	}

	// Change player position
	player->Move();

	if (counter % 100 == 0) {
		for (int i = 0; i < NUMBER_OF_BASIC_ENEMIES; i++) {
			for (int j = i * NUMBER_OF_BULLETS; j < (i * NUMBER_OF_BULLETS) + NUMBER_OF_BULLETS; j++) {
				basicEnemyBullets[j] = new Bullet("assets/bullet.bmp", renderer, basicEnemies[i]->getPosX(), basicEnemies[i]->getPosY());
			}
		}

		for (int i = 0; i < DIRECTIONS; i++) {
			movingEnemyBullets[i] = new Bullet("assets/bullet.bmp", renderer, movingEnemy->getActualX(), movingEnemy->getActualY());
		}
	}

	for (int i = 0; i < NUMBER_OF_BASIC_ENEMIES; i++) {
		basicEnemyBullets[i * NUMBER_OF_BULLETS]->Move(BULLET_VELOCITY, 0);
		basicEnemyBullets[i * NUMBER_OF_BULLETS + 1]->Move(-BULLET_VELOCITY, 0);
		basicEnemyBullets[i * NUMBER_OF_BULLETS + 2]->Move(0, BULLET_VELOCITY);
		basicEnemyBullets[i * NUMBER_OF_BULLETS + 3]->Move(0, -BULLET_VELOCITY);
	}

	movingEnemyBullets[0]->Move(BULLET_VELOCITY, 0);
	movingEnemyBullets[1]->Move(-BULLET_VELOCITY, 0);
	movingEnemyBullets[2]->Move(0, BULLET_VELOCITY);
	movingEnemyBullets[3]->Move(0, -BULLET_VELOCITY);
	movingEnemyBullets[4]->Move(-BULLET_VELOCITY, -BULLET_VELOCITY);
	movingEnemyBullets[5]->Move(BULLET_VELOCITY, BULLET_VELOCITY);
	movingEnemyBullets[6]->Move(BULLET_VELOCITY, -BULLET_VELOCITY);
	movingEnemyBullets[7]->Move(-BULLET_VELOCITY, BULLET_VELOCITY);
}

// Update entity positions and other data
void Game::update() {
	// Center camera over the player
	camera.x = (player->getPosX() + ENTITY_SIZE / 2) - SCREEN_WIDTH / 2;
	camera.y = (player->getPosY() + ENTITY_SIZE / 2) - SCREEN_HEIGHT / 2;

	// Keep camera in bounds
	if (camera.x < 0) {
		camera.x = 0;
	}
	if (camera.y < 0) {
		camera.y = 0;
	}
	if (camera.x > LEVEL_WIDTH - camera.w) {
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if (camera.y > LEVEL_HEIGHT - camera.h) {
		camera.y = LEVEL_HEIGHT - camera.h;
	}

	player->Update(camera.x, camera.y);

	for (int i = 0; i < NUMBER_OF_BASIC_ENEMIES; i++) {
		basicEnemies[i]->Update(camera.x, camera.y);
	}

	movingEnemy->UpdateMoving(camera.x, camera.y);

	for (int i = 0; i < NUMBER_OF_ALL_BULLETS; i++) {
		basicEnemyBullets[i]->Update(camera.x, camera.y);
	}

	for (int i = 0; i < DIRECTIONS; i++) {
		movingEnemyBullets[i]->Update(camera.x, camera.y);
	}

	if (player->getInvincibilityFrames() < counter) {
		for (int i = 0; i < NUMBER_OF_ALL_BULLETS; i++) {
			// Remove extra player space taken by the thruster
			SDL_Rect playerRect = player->getRect();
			playerRect.w = ENTITY_SIZE * 2;
			playerRect.h = ENTITY_SIZE * 2;

			if (checkColiision(playerRect, basicEnemyBullets[i]->getRect())) {
				player->setInvincibility(counter + INVINCIBILITY_FRAMES);
				player->setHp();
				if (!player->getHp()) {
					isGameOver = true;
				}
				break;
			}
		}

		for (int i = 0; i < DIRECTIONS; i++) {
			// Remove extra player space taken by the thruster
			SDL_Rect playerRect = player->getRect();
			playerRect.w = ENTITY_SIZE * 2;
			playerRect.h = ENTITY_SIZE * 2;

			if (checkColiision(playerRect, movingEnemyBullets[i]->getRect())) {
				player->setInvincibility(counter + INVINCIBILITY_FRAMES);
				player->setHp();
				if (!player->getHp()) {
					isGameOver = true;
				}
				break;
			}
		}
	}

	counter++;

	char text[128];
	sprintf_s(text, "Time: %d", realTime);
	timer = new Label("assets/timerLabel.bmp", renderer, SCREEN_WIDTH - (ENTITY_SIZE * 6), 5, text, true);
}

// Handle mouse and keyboard input in main menu
void Game::handleMenuEvents() {
	SDL_Event event;
	SDL_Point mousePosition;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				isRunning = false;
			}

			if (event.key.keysym.sym == SDLK_n) {
				isNewGame = true;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			mousePosition.x = event.motion.x;
			mousePosition.y = event.motion.y;

			if (SDL_PointInRect(&mousePosition, startButton->getRect())) {
				isNewGame = true;
			}

			if (SDL_PointInRect(&mousePosition, exitButton->getRect())) {
				isRunning = false;
			}
			break;
		default:
			break;
		}
	}
}

// Handle mouse and keyboard input in game over screen
void Game::handleGameOverEvents() {
	SDL_Event event;
	SDL_Point mousePosition;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				isRunning = false;
			}

			if (event.key.keysym.sym == SDLK_n) {
				isNewGame = true;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			mousePosition.x = event.motion.x;
			mousePosition.y = event.motion.y;

			if (SDL_PointInRect(&mousePosition, gameOverButton->getRect())) {
				isNewGame = true;
			}

			if (SDL_PointInRect(&mousePosition, menuButton->getRect())) {
				isGameOver = false;
				isMenuActive = true;
			}
			break;
		default:
			break;
		}
	}
}

// Render entities
void Game::render() {
	SDL_RenderClear(renderer);

	BGTexture->Render(0, 0, &camera);
	player->Render();
	timer->Render();

	for (int i = 0; i < NUMBER_OF_BASIC_ENEMIES; i++) {
		basicEnemies[i]->Render();
	}

	movingEnemy->Render();

	for (int i = 0; i < NUMBER_OF_ALL_BULLETS; i++) {
		basicEnemyBullets[i]->Render();
	}

	for (int i = 0; i < DIRECTIONS; i++) {
		movingEnemyBullets[i]->Render();
	}


	for (int i = 0; i < player->getHp(); i++) {
		health[i]->Render();
	}

	SDL_RenderPresent(renderer);
}

// Render menu
void Game::renderMenu() {
	SDL_RenderClear(renderer);
	MenuBGTexture->Render(0, 0, &camera);
	startButton->Render();
	exitButton->Render();
	SDL_RenderPresent(renderer);
}

// Render game over screen
void Game::renderGameOver() {
	SDL_RenderClear(renderer);
	MenuBGTexture->Render(0, 0, &camera);
	gameOverButton->Render();
	menuButton->Render();
	SDL_RenderPresent(renderer);
}

// Free memory
void Game::clean() {
	BGTexture->Clean();
	MenuBGTexture->Clean();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}