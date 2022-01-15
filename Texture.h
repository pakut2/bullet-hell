#include <SDL.h>
#include <SDL_image.h>

class Texture
{
public:
	//Initializes variables
	Texture(SDL_Renderer* ren);

	//Deallocates memory
	~Texture();

	//Loads image at specified path
	bool LoadFromFile(const char* path);

	//Deallocates texture
	void Clean();

	// Renders texture at given point
	void Render(int x, int y, SDL_Rect* clip = NULL);

	int GetWidth();
	int GetHeight();

private:
	SDL_Texture* texture;
	SDL_Renderer* renderer;

	// Image dimensions
	int Width;
	int Height;
};