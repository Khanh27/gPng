#pragma once
#include <SDL2/SDL.h>


class Game {
	public:
		Game();

		bool Initialize();

		void runLoop();

		void shutDown();

	private:
		void processInput();
		void updateGame();
		void GenerateOutput();

		SDL_Window* mWindow;
		bool mIsRunning;
};