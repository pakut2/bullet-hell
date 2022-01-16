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
		destRect.w = ENTITY_SIZE * 6;
		destRect.h = ENTITY_SIZE * 2;
	}
	else {
		destRect.w = LABEL_WIDTH * 2;
		destRect.h = LABEL_HEIGHT * 2;
	}

	destRect.x = PosX;
	destRect.y = PosY;
}

Label::~Label() {
	SDL_DestroyTexture(texture);
}

void Label::Render() {
	SDL_RenderCopy(renderer, texture, NULL, &destRect);
}