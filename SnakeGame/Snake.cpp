#include "Snake.h"
#include "SnakePart.h"
#include "Utils.h"
#include <iostream>

Snake::Snake(SDL_Renderer *renderer, int x, int y, int direction) : renderer(renderer), head(nullptr) {
	addBody();
	head->setDirection(direction);
	head->setX(x);
	head->setY(y);

	addBody();
	addBody();
}

void Snake::destructSnakeBody() {
	SnakePart* c_ptr = head;
	SnakePart* n_ptr = head->getNext();

	bool isDone = false;
	do {
		delete c_ptr;
		if (n_ptr == nullptr) isDone = true;
		else {
			c_ptr = n_ptr;
			n_ptr = n_ptr->getNext();
		}

	} while (!isDone);
	
}

Snake::~Snake() {
	destructSnakeBody();
}

SnakePart* Snake::getHead() { return head; }

void Snake::addBody() {
	SnakePart* new_element { nullptr };
	
	SnakePart* cur_ptr = head;
	
	if (cur_ptr == nullptr) {
		new_element = new SnakePart(renderer, 0, TILE_ROW / 2, right);
		head = new_element;
	}


	else {
		while (cur_ptr->getNext() != nullptr) {
			cur_ptr = cur_ptr->getNext();
		}
	
		new_element = new SnakePart(renderer, *cur_ptr);
		cur_ptr->setNext(new_element);
	}

}

void Snake::update() {

	auto p_ptr = head;
	auto c_ptr = head->getNext();

	while (c_ptr != nullptr) {
		c_ptr->updateRelativeDirection(*p_ptr);
		
		p_ptr = c_ptr;
		c_ptr = c_ptr->getNext();
	}

	c_ptr = head;
	while (c_ptr != nullptr) {
		c_ptr->updatePosition();
		c_ptr = c_ptr->getNext();
	}
		
}

void Snake::changeDirection(int _direction) {
	int headDirection = head->getDirection();
	if ((headDirection == left && _direction == right) || (headDirection == right && _direction == left) ||
		(headDirection == up && _direction == down) || (headDirection == down && _direction == up)
		) 
	{
		reverseSnake();
	}

	head->setDirection(_direction);
}

void Snake::reverseSnake() {
	SnakePart* p_ptr{ nullptr };
	SnakePart* c_ptr{ head };
	SnakePart* n_ptr{ nullptr };

	if (head->getNext() != nullptr) {
		n_ptr = c_ptr->getNext();
	
		bool isDone = false;
		do {
			c_ptr->setNext(p_ptr);

			if (n_ptr != nullptr) {
				p_ptr = c_ptr;
				c_ptr = n_ptr;
				n_ptr = n_ptr->getNext();
			}

			else isDone = true;

		} while (!isDone);

		head = c_ptr;
	}	
}

bool Snake::collideItself() {
	int headX = head->getX();
	int headY = head->getY();

	SnakePart* cur_ptr = head->getNext();
	bool isCollide = false;

	while (cur_ptr != nullptr && !isCollide) {
		if (headX == cur_ptr->getX() && headY == cur_ptr->getY()) {
			isCollide = true;
		}

		cur_ptr = cur_ptr->getNext();
	}
	
	return isCollide;
}

void Snake::render() {
	SnakePart* cur_ptr = head;
	while (cur_ptr != nullptr) {
		cur_ptr->render(renderer);
		cur_ptr = cur_ptr->getNext();
	}

}