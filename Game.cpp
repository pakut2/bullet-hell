#include <math.h>
#include "Game.hpp"
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Constants.h"
#include "utils.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Label.h"

// Entities
Player* player;
Enemy* basicEnemies[NUMBER_OF_BASIC_ENEMIES];
Enemy* curveEnemies[NUMBER_OF_CURVE_ENEMIES];
Enemy* movingEnemy;
Bullet* basicEnemyBullets[NUMBER_OF_ALL_BASIC_BULLETS];
Bullet* curveEnemyBullets[NUMBER_OF_ALL_CURVE_BULLETS];
Bullet* movingEnemyBullets[DIRECTIONS];
GameObject* health[PLAYER_HEALTH];
SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

// Backgrounds and menu labels
TextureManager* BGTexture;
TextureManager* MenuBGTexture;
Label* startButton;
Label* exitButton;
Label* gameOverButton;
Label* menuButton;
Label* timer;

// Create enemies and corresponding bullets
void createEnemies(SDL_Renderer* renderer, Enemy* enemies[], Bullet* bullets[], const int numberOfEnemies) {
	for (int i = 0; i < numberOfEnemies; i++) {
		int randomX = random(0, LEVEL_WIDTH);
		int randomY = random(0, LEVEL_HEIGHT);

		enemies[i] = new Enemy("assets/enemy.bmp", renderer, randomX, randomY);

		for (int j = i * NUMBER_OF_BULLETS; j < (i * NUMBER_OF_BULLETS) + NUMBER_OF_BULLETS; j++) {
			bullets[j] = new Bullet("assets/bullet.bmp", renderer, randomX, randomY);
		}
	}
}

// Shoot new bullets
void shoot(SDL_Renderer* renderer, Enemy* enemies[], Bullet* bullets[], const int numberOfEnemies) {
	for (int i = 0; i < numberOfEnemies; i++) {
		for (int j = i * NUMBER_OF_BULLETS; j < (i * NUMBER_OF_BULLETS) + NUMBER_OF_BULLETS; j++) {
			bullets[j] = new Bullet("assets/bullet.bmp", renderer, enemies[i]->getPosX(), enemies[i]->getPosY());
		}
	}
}

// Update entities
void updateEnemies(Enemy* enemies[], const int numberOfEntites) {
	for (int i = 0; i < numberOfEntites; i++) {
		enemies[i]->Update(camera.x, camera.y);
	}
}

void updateBullets(Bullet* bullets[], const int numberOfEntites) {
	for (int i = 0; i < numberOfEntites; i++) {
		bullets[i]->Update(camera.x, camera.y);
	}
}

// Render entities
void renderEnemies(Enemy* enemies[], const int numberOfEntites) {
	for (int i = 0; i < numberOfEntites; i++) {
		enemies[i]->Render();
	}
}

void renderBullets(Bullet* bullets[], const int numberOfEntites) {
	for (int i = 0; i < numberOfEntites; i++) {
		bullets[i]->Render();
	}
}

Game::Game() {}

Game::~Game() {
	clean();
}

// Init SDL
void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen) {
	counter = 0;
	isGameOver = false;
	isMenuActive = true;
	bulletAngle = 0;
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

	BGTexture = new TextureManager(renderer);
	BGTexture->LoadFromFile("assets/bg.bmp");

	MenuBGTexture = new TextureManager(renderer);
	MenuBGTexture->LoadFromFile("assets/menubg.bmp");

	startButton = new Label("assets/start.bmp", renderer, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 2 - 120, "", false);
	exitButton = new Label("assets/exit.bmp", renderer, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 2 + 60, "", false);
	gameOverButton = new Label("assets/over.bmp", renderer, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 2 - 120, "", false);
	menuButton = new Label("assets/menu.bmp", renderer, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 2 + 60, "", false);

	createEnemies(renderer, basicEnemies, basicEnemyBullets, NUMBER_OF_BASIC_ENEMIES);
	createEnemies(renderer, curveEnemies, curveEnemyBullets, NUMBER_OF_CURVE_ENEMIES);

	movingEnemy = new Enemy("assets/enemy.bmp", renderer, LEVEL_WIDTH / 2, LEVEL_HEIGHT / 2);

	for (int i = 0; i < DIRECTIONS; i++) {
		movingEnemyBullets[i] = new Bullet("assets/bullet.bmp", renderer, LEVEL_WIDTH / 2, (LEVEL_HEIGHT / 2) + ENEMY_RADIUS);
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

		player->HandleEvent(event);
	}

	player->Move();

	// Shoot bullets in interval
	if (counter % 50 == 0 && counter % 100 != 0) {
		shoot(renderer, basicEnemies, basicEnemyBullets, NUMBER_OF_BASIC_ENEMIES);
	}

	if (counter % 100 == 0) {
		shoot(renderer, curveEnemies, curveEnemyBullets, NUMBER_OF_CURVE_ENEMIES);
	}

	if (counter % 200 == 0) {
		for (int i = 0; i < DIRECTIONS; i++) {
			movingEnemyBullets[i] = new Bullet("assets/bullet.bmp", renderer, movingEnemy->getActualX(), movingEnemy->getActualY());
		}
	}

	// Move bullets
	for (int i = 0; i < NUMBER_OF_BASIC_ENEMIES; i++) {
		basicEnemyBullets[i * NUMBER_OF_BULLETS]->Move(BULLET_VELOCITY, 0);
		basicEnemyBullets[i * NUMBER_OF_BULLETS + 1]->Move(-BULLET_VELOCITY, 0);
		basicEnemyBullets[i * NUMBER_OF_BULLETS + 2]->Move(0, BULLET_VELOCITY);
		basicEnemyBullets[i * NUMBER_OF_BULLETS + 3]->Move(0, -BULLET_VELOCITY);
	}

	for (int i = 0; i < NUMBER_OF_CURVE_ENEMIES; i++) {
		curveEnemyBullets[i * NUMBER_OF_BULLETS]->Move(BULLET_VELOCITY, BULLET_RADIUS * cos(bulletAngle));
		curveEnemyBullets[i * NUMBER_OF_BULLETS + 1]->Move(-BULLET_VELOCITY, BULLET_RADIUS * cos(bulletAngle));
		curveEnemyBullets[i * NUMBER_OF_BULLETS + 2]->Move(BULLET_RADIUS * sin(bulletAngle), BULLET_VELOCITY);
		curveEnemyBullets[i * NUMBER_OF_BULLETS + 3]->Move(BULLET_RADIUS * sin(bulletAngle), -BULLET_VELOCITY);
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

bool checkCollisionForPlayer(Bullet* bullets[], const int numberOfBullets, const int counter) {
	for (int i = 0; i < numberOfBullets; i++) {
		// Remove extra player space taken by the thruster
		SDL_Rect playerRect = player->getRect();
		playerRect.w = ENTITY_SIZE * 2;
		playerRect.h = ENTITY_SIZE * 2;

		if (checkColiision(playerRect, bullets[i]->getRect())) {
			player->setInvincibility(counter + INVINCIBILITY_FRAMES);
			player->setHp();
			if (!player->getHp()) {
				return true;
			}
			break;
		}
	}

	return false;
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

	updateEnemies(basicEnemies, NUMBER_OF_BASIC_ENEMIES);
	updateEnemies(curveEnemies, NUMBER_OF_CURVE_ENEMIES);
	movingEnemy->UpdateMoving(camera.x, camera.y);

	updateBullets(basicEnemyBullets, NUMBER_OF_ALL_BASIC_BULLETS);
	updateBullets(curveEnemyBullets, NUMBER_OF_ALL_CURVE_BULLETS);
	updateBullets(movingEnemyBullets, DIRECTIONS);

	// Check for collision
	if (player->getInvincibilityFrames() < counter) {
		bool gameOver[NUMBER_OF_ENEMY_TYPES];
		gameOver[0] = checkCollisionForPlayer(basicEnemyBullets, NUMBER_OF_ALL_BASIC_BULLETS, counter);
		gameOver[1] = checkCollisionForPlayer(curveEnemyBullets, NUMBER_OF_ALL_CURVE_BULLETS, counter);
		gameOver[2] = checkCollisionForPlayer(movingEnemyBullets, DIRECTIONS, counter);

		for (int i = 0; i < NUMBER_OF_ENEMY_TYPES; i++) {
			if (gameOver[i]) {
				isGameOver = true;
			}
		}
	}

	bulletAngle += 0.05;
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

	renderEnemies(basicEnemies, NUMBER_OF_BASIC_ENEMIES);
	renderEnemies(curveEnemies, NUMBER_OF_CURVE_ENEMIES);
	movingEnemy->Render();

	if (counter > 50) {
		renderBullets(basicEnemyBullets, NUMBER_OF_ALL_BASIC_BULLETS);
	}
	renderBullets(curveEnemyBullets, NUMBER_OF_ALL_CURVE_BULLETS);
	renderBullets(movingEnemyBullets, DIRECTIONS);

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