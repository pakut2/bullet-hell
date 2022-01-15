#include "Label.h"
#include "TextureManager.h"
#include "Constants.h"

Label::Label(const char* textureSheet, SDL_Renderer* ren, int x, int y, const char* text, bool small) {
	renderer = ren;
	texture = TextureManager::LoadLabelTexture(textureSheet, ren, text);

	// Init position
	PosX = x;
	PosY = y;

	if (small) {
		entityRect.w = ENTITY_SIZE * 6;
		entityRect.h = ENTITY_SIZE * 2;
	}
	else {
		entityRect.w = LABEL_WIDTH * 2;
		entityRect.h = LABEL_HEIGHT * 2;
	}

	entityRect.x = PosX;
	entityRect.y = PosY;
}

Label::~Label() {
	SDL_DestroyTexture(texture);
}

void Label::Render() {
	SDL_RenderCopy(renderer, texture, NULL, &entityRect);
}