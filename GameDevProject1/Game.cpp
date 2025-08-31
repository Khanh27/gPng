#include "Game.h"

#include <iostream>

Game::Game()
	:window(nullptr)
	, isRunning(true)
	, renderer(nullptr)
	, mPaddlePos({ 50.0f, 300.0f })
	, mBallPos({ 400.0f, 300.0f })
	, mTicksCount(0)
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
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	mTicksCount = SDL_GetTicks();

}
void Game::generateOutputs() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderClear(renderer); 

	//draw
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect wall{
		0,
		0,
		800, //width
		15 //height
	};
	SDL_RenderFillRect(renderer, &wall);

	wall.y = 600 - 15;
	SDL_RenderFillRect(renderer, &wall);

	wall.x = 800 - 15;
	wall.y = 0;
	wall.w = 15;
	wall.h = 600;
	SDL_RenderFillRect(renderer, &wall);

	SDL_Rect ball{
		static_cast<int>(mBallPos.x - 15 / 2),
		static_cast<int>(mBallPos.y - 15 / 2),
		15,
		15
	};
	SDL_RenderFillRect(renderer, &ball);

	SDL_Rect paddle{
		0,
		static_cast<int>(mPaddlePos.y - 150 / 2),
		15,
		150
	};
	SDL_RenderFillRect(renderer, &paddle);

	SDL_RenderPresent(renderer);

}