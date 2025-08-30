#include <SDL2/SDL.h>
#include <stdio.h>

#include "Game.h"

int main(int argc, char** argv) {
	Game game;
	bool success = game.Initialize();
	if (success) {
		game.runGameLoop();
	}

	game.Shutdown();
	return 0;
}
