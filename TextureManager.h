#include "Game.hpp"

class TextureManager {
public:
	TextureManager(SDL_Renderer* ren);
	~TextureManager();

	bool LoadFromFile(const char* path);

	void Render(int x, int y, SDL_Rect* clip = NULL);
	void Clean();

	int GetWidth();
	int GetHeight();

	static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);
	static SDL_Texture* LoadLabelTexture(const char* fileName, SDL_Renderer* ren, const char* text);
private:
	SDL_Texture* texture;
	SDL_Renderer* renderer;

	int imageWidth;
	int imageHeight;
};