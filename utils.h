#include <cstdlib>
#include <ctime>

int random(int min, int max) {
	static bool first = true;

	// Seed only once
	if (first) {
		srand(time(NULL));
		first = false;
	}

	return min + rand() % ((max + 1) - min);
}

// AABB collision detection
bool checkColiision(SDL_Rect rectA, SDL_Rect rectB) {
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	// Sides of rectangles
	leftA = rectA.x;
	rightA = rectA.x + rectA.w;
	topA = rectA.y;
	bottomA = rectA.y + rectA.h;

	leftB = rectB.x;
	rightB = rectB.x + rectB.w;
	topB = rectB.y;
	bottomB = rectB.y + rectB.h;

	// If any of the sides from A are outside of B
	if (bottomA <= topB) {
		return false;
	}

	if (topA >= bottomB) {
		return false;
	}

	if (rightA <= leftB) {
		return false;
	}

	if (leftA >= rightB) {
		return false;
	}

	// If none of the sides from A are outside B
	return true;
}