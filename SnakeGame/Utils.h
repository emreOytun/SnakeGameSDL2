#ifndef UTILS_H
#define UTILS_H
#include <SDL.h>
#include <SDL_image.h>

constexpr auto TILE_W = 20;
constexpr auto TILE_H = 20;
constexpr auto TILE_ROW = 40;
constexpr auto TILE_COL = 40;

constexpr auto SNAKE_W = 20;
constexpr auto SNAKE_H = 20;
constexpr auto SNAKE_ROW = 40;
constexpr auto SNAKE_COL = 40;

namespace TextureManager {
	SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path);

	void renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* destRect);
}


#endif