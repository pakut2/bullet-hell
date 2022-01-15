#include "TextureManager.h"

void DrawString(SDL_Surface* surface, int x, int y, const char* text) {
	SDL_Surface* charset = SDL_LoadBMP("assets/charset.bmp");

	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;

	while (*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, surface, &d);
		x += 8;
		text++;
	};

	SDL_FreeSurface(charset);
};

SDL_Texture* TextureManager::LoadTexture(const char* filename, SDL_Renderer* renderer) {
	SDL_Surface* surface = SDL_LoadBMP(filename);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	return texture;
}

SDL_Texture* TextureManager::LoadLabelTexture(const char* filename, SDL_Renderer* renderer, const char* text) {
	SDL_Surface* surface = SDL_LoadBMP(filename);
	SDL_Rect surfaceRect = surface->clip_rect;

	DrawString(surface, surfaceRect.x + surfaceRect.w / 3, surface->clip_rect.y, text);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	return texture;
}