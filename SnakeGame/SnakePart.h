#ifndef SNAKE_PART_H
#define SNAKE_PART_H

#include <SDL.h>
#include <queue>

enum directions {up, right, down, left};

class SnakePart
{
private :
	SDL_Texture* text;
	SDL_Rect destRect; // x, y, w, h;
	
	int x, y;
	int direction;

	SnakePart* next;
	void initializeRelative(const SnakePart& oth);

public :
	SnakePart(SDL_Renderer* renderer, int x, int y, int direction);
	SnakePart(SDL_Renderer* renderer, const SnakePart& oth);

	int getX() const;
	void setX(int _x);

	int getY() const;
	void setY(int _y);

	int getRelativeDirection(const SnakePart& othPart) const;
	int getDirection() const;
	void setDirection(int d);

	void setNext(SnakePart* _next);
	SnakePart* getNext() const;

	void updatePosition();
	void updateRelativeDirection(const SnakePart& oth);
	void render(SDL_Renderer* renderer);

};

#endif

