#include "Game.h"

#include <iostream>

Game::Game()
	:window(nullptr)
	, isRunning(true)
	, renderer(nullptr)
	, mPaddlePos({ 50.0f, 300.0f })
	, mPaddle2Pos({ 50.0f, 300.0f })
	, mBallPos({ 400.0f, 300.0f })
	, mTicksCount(0)
	, mPaddleDir(0)
	, mPaddle2Dir(0)
	, combo (0) //make sure to reset
	, comboMilestone(0)
	, speedMultiplier(1.0f)
	, initialBallVel({ -200.0f, 235.0f })
	, mBallVel({ -200.0f, 235.0f })
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
		800, //width
		600, //height
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

	mPaddleDir = 0;
	if (state[SDL_SCANCODE_W]) {
		mPaddleDir -= 1;
	}

	if (state[SDL_SCANCODE_S]) {
		mPaddleDir += 1;
	}

	mPaddle2Dir = 0;
	if (state[SDL_SCANCODE_I]) {
		mPaddle2Dir -= 1;
	}

	if (state[SDL_SCANCODE_K]) {
		mPaddle2Dir += 1;
	}
}
void Game::updateGame() {
	std::cout << combo << std::endl;
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	if (deltaTime > 0.5f) {
		deltaTime = 0.5f;
	}

	mTicksCount = SDL_GetTicks();

	if (mPaddleDir != 0) {
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;

		if (mPaddlePos.y < 90.0f) {  // 15 + 75
			mPaddlePos.y = 90.0f;
		}
		
		else if (mPaddlePos.y > 510.0f) {  // 585 - 75
			mPaddlePos.y = 510.0f;
		}
	}

	if (mPaddle2Dir != 0) {
		mPaddle2Pos.y += mPaddle2Dir * 300.0f * deltaTime;

		if (mPaddle2Pos.y < 90.0f) {  // 15 + 75
			mPaddle2Pos.y = 90.0f;
		}

		else if (mPaddle2Pos.y > 510.0f) {  // 585 - 75
			mPaddle2Pos.y = 510.0f;
		}
	}

	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	if (mBallPos.y <= 15 && mBallVel.y < 0.0f) {
		mBallVel.y *= -1;
	}

	if (mBallPos.y >= 585 && mBallVel.y > 0.0f) {
		mBallVel.y *= -1;
	}

	float diffPaddle2 = abs(mBallPos.y - mPaddle2Pos.y);
	if (diffPaddle2 <= 150/2.0f && mBallPos.x <= 785.0f && mBallPos.x >= 780.0f && mBallVel.x > 0.0f) {
		mBallVel.x *= -1;
		combo += 1;
	}

	float diff = abs(mBallPos.y - mPaddlePos.y);
	if (diff <= 150 / 2.0f && mBallPos.x <= 25.0f && mBallPos.x >= 20.0f && mBallVel.x < 0.0f) {
		mBallVel.x *= -1;
		combo += 1;
	}

	if (combo > 0 && combo % 10 == 0 && combo != comboMilestone) {
		comboMilestone = combo;
		speedMultiplier += 0.5f;

		//float len = sqrt(mBallVel.x * mBallVel.x + mBallVel.y * mBallVel.y);
		mBallVel.x = mBallVel.x * speedMultiplier;
		mBallVel.y = mBallVel.y * speedMultiplier;
	}

	if (mBallPos.x > 785.0f && mBallVel.x > 0.0f) {
		mBallPos.x = 400.0f;
		mBallPos.y = 300.0f;
		combo = 0;
		comboMilestone = 0;
		speedMultiplier = 1.0f;
		mBallVel = initialBallVel;
	}

	if (mBallPos.x < 20.0f && mBallVel.x < 0.0f) {
		mBallPos.x = 400.0f;
		mBallPos.y = 300.0f;
		combo = 0;
		comboMilestone = 0;
		speedMultiplier = 1.0f;
		mBallVel = initialBallVel;
	}
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

	/*
	wall.x = 800 - 15;
	wall.y = 0;
	wall.w = 15;
	wall.h = 600;
	SDL_RenderFillRect(renderer, &wall);
	*/

	if (combo >= 10) {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	}

	SDL_Rect ball{
		static_cast<int>(mBallPos.x - 15 / 2),
		static_cast<int>(mBallPos.y - 15 / 2),
		15,
		15
	};
	SDL_RenderFillRect(renderer, &ball);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_Rect paddle{
		0,
		static_cast<int>(mPaddlePos.y - 150 / 2),
		15,
		150
	};
	SDL_RenderFillRect(renderer, &paddle);

	SDL_Rect paddle2{
		800 - 15,
		static_cast<int>(mPaddle2Pos.y - 150 / 2),
		15,
		150
	};
	SDL_RenderFillRect(renderer, &paddle2);

	SDL_RenderPresent(renderer);

}