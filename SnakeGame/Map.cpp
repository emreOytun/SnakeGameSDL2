#include "Map.h"
#include "Utils.h"
#include <cstdlib>
#include <time.h>
#include <iostream>

Map::Map(SDL_Renderer* renderer) : renderer(renderer), tile1_rect() {
	map = std::vector<std::vector<int>>(TILE_ROW, std::vector<int>(TILE_COL, 0));
	tile1 = TextureManager::loadTexture(renderer, "assets/tile1.png");
	target = TextureManager::loadTexture(renderer, "assets/target.png");

	tile1_rect.w = TILE_W;
	tile1_rect.h = TILE_H;

	target_rect.w = TILE_W;
	target_rect.h = TILE_H;
	
}

Map::~Map() {
	SDL_DestroyTexture(target);
	SDL_DestroyTexture(tile1);
}

void Map::render() {
	int type{};

	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			type = map[i][j];
			
			switch (type) {

			case 0:
				tile1_rect.x = j * TILE_W;
				tile1_rect.y = i * TILE_H;
				TextureManager::renderTexture(renderer, tile1, nullptr, &tile1_rect);
				break;

			case 1 :
				target_rect.x = j * TILE_W;
				target_rect.y = i * TILE_H;
				TextureManager::renderTexture(renderer, target, nullptr, &target_rect);
				break;
			}
		}
	}
}

void Map::add_target(const int& snakeX, const int& snakeY) {
	do {
		targetX = rand() % TILE_COL;
	} while (snakeX == targetX) ;

	do {
		targetY = rand() % TILE_ROW;
	} while (snakeY == targetY);

	map[targetY][targetX] = 1;
}

void Map::delete_target() {
	map[targetY][targetX] = 0;
}

bool Map::check_collision(const int& snakeX, const int& snakeY) {
	if (snakeX == targetX && snakeY == targetY) return true;
	std::cout << "snake:" << "(" << snakeX << "," << snakeY << ")" << std::endl;
	std::cout << "target:" << "(" << targetX << "," << targetY << ")" << std::endl;
	return false;
}




