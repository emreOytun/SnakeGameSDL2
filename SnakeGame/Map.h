#pragma once
#include <vector>
#include <SDL.h>

class Map
{
private:
	std::vector<std::vector<int>> map;
	SDL_Renderer* renderer;

	SDL_Texture* tile1;
	SDL_Rect tile1_rect;

	SDL_Texture* target;
	SDL_Rect target_rect;
	int targetX, targetY;

public:
	Map(SDL_Renderer* renderer);
	~Map();
	Map(const Map&) = delete;
	Map& operator=(const Map&) = delete;

	void render();
	
	void add_target(const int& snakeX, const int& snakeY);
	void delete_target();
	bool check_collision(const int& snakeX, const int& snakeY);

};

