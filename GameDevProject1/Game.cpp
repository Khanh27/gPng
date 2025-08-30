#include "Game.h"

#include <iostream>

Game::Game() 
	:window(nullptr)
	,isRunning(true)
	,renderer(nullptr)
	{
	}



bool Game::Initialize() {
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow(
		"pong game",
		100,
		100,
		800,
		600,
		SDL_WINDOW_RESIZABLE
	);

	if (!window) {
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(
		window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!renderer) {
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false; 
	}

	return true;
}

void Game::Shutdown() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::runGameLoop() {
	while (isRunning) {
		processInputs();
		updateGame();
		generateOutputs();
	}
}

void Game::processInputs() {
	SDL_Event event; 

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE]) {
		isRunning = false;
	}
}
void Game::updateGame() {

}
void Game::generateOutputs() {

}