/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

// Using SDL and standard IO
#include <SDL.h>
#include "Game.h"

void InitSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize. SDL_Error: %s\n", SDL_GetError());
	}
}

void CloseSDL() {
	SDL_Quit();
}

int main(int argc, char* args[])
{
	InitSDL();
	Game game;
	// Game loop
	while (!game.IsDone()) {
		game.HandleInput();
		game.Update();
		game.Render();
		game.ManageTime();
	}

	game.~Game();
	CloseSDL();
	return 0;
}