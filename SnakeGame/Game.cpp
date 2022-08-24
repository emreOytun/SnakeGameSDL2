#include "Game.h"
#include "SnakePart.h"
#include "Snake.h"
#include "Map.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Game::Game() = default;
Game::~Game() {
	clean();
	std::cout << "GAME DESTROYED!" << std::endl;
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {

	isRunning = false;

	// Always check after initializing SDL, windows, renderers etc.

	int flags{ 0 };
	if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;

	// Create and Check if sdl is initialized successfuly.
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialized!..." << std::endl;

		// Create and Check if window is initialized successfully.
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			std::cout << "Window created!" << std::endl;

			// Create and Check if renderer is initialized successfully.
			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer) {
				std::cout << "Renderer created!" << std::endl;

				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			}

			isRunning = true; // If everything is initialized, then mark isRunning as true.
		}
	}

	// Initialize texture here for now. After we'll create TextureManager to initialize/delete all textures.
	if (isRunning) {	
		snake = new Snake(renderer, 0, 0, right);
		map = new Map(renderer);
		map->add_target(snake->getHead()->getX(), snake->getHead()->getY());
	}

	std::cout << "GAME created!" << std::endl;
}

void Game::handleEvents() {

	SDL_PollEvent(&Game::event);

	switch (Game::event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;

	case SDL_KEYDOWN :
		if (Game::event.key.keysym.sym == SDLK_w) {
			snake->changeDirection(up);
		}
		
		else if (Game::event.key.keysym.sym == SDLK_s) {
			snake->changeDirection(down);
		}

		else if (Game::event.key.keysym.sym == SDLK_d) {
			snake->changeDirection(right);
		}

		else if (Game::event.key.keysym.sym == SDLK_a) {
			snake->changeDirection(left);
		}
			
		break;
		
	default:
		break;
	}
}

void Game::update() {
	snake->update();
	
	
	if (snake->collideItself()) {
		std::cout << "GAME OVER !\n";
		isRunning = false;
	}
	

	if (map->check_collision(snake->getHead()->getX(), snake->getHead()->getY())) {
		map->delete_target();
		snake->addBody();
		map->add_target(snake->getHead()->getX(), snake->getHead()->getY());
		total_points++;
	}
	
}

void Game::render() {
	SDL_RenderClear(renderer); // Clear render buffer

	map->render();
	snake->render();

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	delete snake;
	//delete map;

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned!" << std::endl;
}
