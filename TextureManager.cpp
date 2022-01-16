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

TextureManager::TextureManager(SDL_Renderer* ren) {
	texture = NULL;
	imageWidth = 0;
	imageHeight = 0;
	renderer = ren;
}

TextureManager::~TextureManager() {
	Clean();
}

bool TextureManager::LoadFromFile(const char* path) {
	Clean();

	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path);

	if (loadedSurface) {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

		if (newTexture) {
			imageWidth = loadedSurface->w;
			imageHeight = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	texture = newTexture;
	return texture != NULL;
}

void TextureManager::Clean() {
	SDL_DestroyTexture(texture);
}

void TextureManager::Render(int x, int y, SDL_Rect* clip) {
	SDL_Rect renderQuad = { x, y, imageWidth, imageHeight };
	SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
}

int TextureManager::GetWidth() {
	return imageWidth;
}

int TextureManager::GetHeight() {
	return imageHeight;
}

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
