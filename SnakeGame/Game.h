#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "Utils.h"


class Snake;
class Map;

class Game
{

public:
	Game();
	~Game();
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	void init(const char* title, int xpos, int ypos, int width, int heigth, bool fullscreen);

	void handleEvents();
	void update();
	void render();

	bool running() const { return isRunning; }

	static SDL_Renderer* renderer;	// Renderer is used in many classes/functions like in TextureManager or GameObject classes therefore it's better to make it public static variable.(Class variable)
	static SDL_Event event;

private:
	bool isRunning;
	SDL_Window* window;
	
	Map* map;
	Snake* snake;
	int total_points;

	void clean();
};


#endif

