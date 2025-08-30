#include "Game.h"

#include <iostream>

Game::Game() 
	:window(nullptr)
	,isRunning(true)
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

	return true;
}

void Game::Shutdown() {
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::runGameLoop() {
	while (isRunning) {
		processInputs();
		updateGame();
		generateOutputs();
	}
}

void processInputs() {

}
void updateGame() {

}
void generateOutputs() {

}