#pragma once
#include "SDL.h"

class SnakeGame
{

private :	
	static SDL_Window window;
	bool isRunning;

public :
	static SDL_Renderer renderer;

	SnakeGame();
	~SnakeGame();
	SnakeGame(const SnakeGame&) = delete;
	SnakeGame& operator=(const SnakeGame&) = delete;

	void init(const char *title, int xpos, int yp)
};

