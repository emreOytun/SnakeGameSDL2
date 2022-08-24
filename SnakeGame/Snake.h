#pragma once
#include <SDL.h>

class SnakePart;

class Snake {
private :
	SnakePart* head;
	SDL_Renderer* renderer;

	void reverseSnake();
	void destructSnakeBody();

public:
	Snake(SDL_Renderer* renderer, int x, int y, int direction);
	~Snake();
	Snake(const Snake&) = delete;
	Snake& operator=(const Snake&) = delete;

	SnakePart* getHead();

	void addBody();
	
	void update();
	void changeDirection(int _direction);
	bool collideItself();

	void render();

};

