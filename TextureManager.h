#include "Game.hpp"

class TextureManager {
public:
	static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);
	static SDL_Texture* LoadLabelTexture(const char* fileName, SDL_Renderer* ren, const char* text);
};