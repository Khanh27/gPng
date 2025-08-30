#pragma once
#include <SDL2/SDL.h>
#include <stdio.h>


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
		bool isRunning;
};