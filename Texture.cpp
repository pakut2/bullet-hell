#include "Texture.h"
#include <stdio.h>

Texture::Texture(SDL_Renderer* ren) {
	// Init
	texture = NULL;
	Width = 0;
	Height = 0;
	renderer = ren;
}

Texture::~Texture() {
	Clean();
}

bool Texture::LoadFromFile(const char* path) {
	Clean();

	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path);

	if (loadedSurface) {
		// Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

		if (newTexture) {
			Width = loadedSurface->w;
			Height = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	texture = newTexture;
	return texture != NULL;
}

void Texture::Clean() {
	SDL_DestroyTexture(texture);
}

// Set rendering space and render to screen
void Texture::Render(int x, int y, SDL_Rect* clip) {
	SDL_Rect renderQuad = { x, y, Width, Height };
	SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
}

int Texture::GetWidth() {
	return Width;
}

int Texture::GetHeight() {
	return Height;
}