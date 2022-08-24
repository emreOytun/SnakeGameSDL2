#include "SnakePart.h"
#include "Utils.h"
#include <iostream>

SnakePart::SnakePart(SDL_Renderer* renderer, int x, int y, int direction) : text(nullptr), next(nullptr), destRect(), x(x), y(y), direction(direction) {
	text = TextureManager::loadTexture(renderer, "assets/body.png");
	
	destRect.x = x * SNAKE_W;
	destRect.y = y * SNAKE_H;
	destRect.w = SNAKE_W;
	destRect.h = SNAKE_H;
}

SnakePart::SnakePart(SDL_Renderer* renderer, const SnakePart& oth) : text(nullptr), next(nullptr), destRect() {
	text = TextureManager::loadTexture(renderer, "assets/body.png");
	initializeRelative(oth);

	destRect.x = x * SNAKE_W;
	destRect.y = y * SNAKE_H;
	destRect.w = SNAKE_W;
	destRect.h = SNAKE_H;
}

int SnakePart::getDirection() const { return direction; }

/* Initiliaze one snake body part relative to the former part location and direction. */
void SnakePart::initializeRelative(const SnakePart& oth) {

	int lastX{oth.getX()}, lastY{oth.getY()};
	direction = oth.getDirection();
	
	switch (direction) {

	case up:
		if (lastY == TILE_ROW - 1) y = 0;
		else y = lastY + 1;
		x = lastX;
		break;

	case down:
		if (lastY == 0) y = TILE_ROW - 1;
		else y = lastY - 1;
		x = lastX;
		break;

	case right:
		if (lastX == 0) x = TILE_COL - 1;
		else x = lastX - 1;
		y = lastY;
		break;

	case left:
		if (lastX == TILE_COL - 1) x = 0;
		else x = lastX + 1;
		y = lastY;
		break;
	}

}

int SnakePart::getX() const { return x; }
void SnakePart::setX(int _x) { x = _x; }

int SnakePart::getY() const { return y; }
void SnakePart::setY(int _y) { y = _y; }

int SnakePart::getRelativeDirection(const SnakePart& othPart) const {
	int otherX = othPart.getX();
	int otherY = othPart.getY();
	
	int relativeDirection{};
	if (x == otherX - 1 || (x == SNAKE_COL - 1 && otherX == 0)) {
		relativeDirection = left;
	}

	else if (x == otherX + 1 || (x == 0 && otherX == SNAKE_COL - 1)) {
		relativeDirection = right;
	}

	else if (y == otherY - 1 || (y == SNAKE_ROW - 1 && otherY == 0)) {
		relativeDirection = up;
	}

	else if (y == otherY + 1 || (y == 0 && otherY == SNAKE_ROW - 1)) {
		relativeDirection = down;
	}

	return relativeDirection;

}

void SnakePart::setDirection(int d) {
	direction = d;
}

void SnakePart::setNext(SnakePart* _next) { next = _next; }
SnakePart* SnakePart::getNext() const { return next; }

void SnakePart::updatePosition() {

	if (direction == up) {
		if (y == 0) y = SNAKE_ROW - 1;
		else y--;
	}

	else if (direction == down) {
		if (y == SNAKE_ROW - 1) y = 0;
		else y++;
	}

	else if (direction== right) {
		if (x == SNAKE_COL - 1) x = 0;
		else x++;
	}

	else if (direction == left) {
		if (x == 0) x = SNAKE_COL - 1;
		else x--;
	}

}

void SnakePart::updateRelativeDirection(const SnakePart& oth) {
	switch (getRelativeDirection(oth)) {

	case up :
		direction = down;
		break;

	case down :
		direction = up;
		break;

	case left :
		direction = right;
		break;

	case right :
		direction = left;
		break;
	}
}

void SnakePart::render(SDL_Renderer* renderer) {
	destRect.x = x * SNAKE_W;
	destRect.y = y * SNAKE_H;
	TextureManager::renderTexture(renderer, text, nullptr, &destRect);
}