#include "Game.h"

#include <iostream>

Game::Game() {
	bool isRunning = true;
	SDL_Window* window = nullptr;
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