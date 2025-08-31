#pragma once
#include <SDL2/SDL.h>
#include <stdio.h>

struct Vector2 {
	float x;
	float y;
};

class Game {
	public:
		Game();

		bool Initialize();
		void runGameLoop();
		void Shutdown();

	private:
		void processInputs();
		void updateGame();
		void generateOutputs();

		SDL_Window* window;
		SDL_Renderer* renderer;
		bool isRunning;
		Vector2 mPaddlePos;
		Vector2 mBallPos;

};