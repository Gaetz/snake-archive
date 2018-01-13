#pragma once
#include <SDL.h>
#include <iostream>
#include <ctime>

#include "Window.h"
#include "Config.h"
#include "World.h"
#include "Vector2.hpp"
#include "RectangleShape.h"
#include "Snake.h"

class Game {

public:
	/** Start game */
	Game();

	/** End game */
	~Game();

	/** Game ending condition */
	bool IsDone();

	/** Manage player's inputs */
	void HandleInput();

	/** Frame update */
	void Update();

	/** Draw game */
	void Render();

	/**
	* \brief Restart time clock
	* Compute delta time and store last tick value.
	*/
	void ManageTime();


private:
	/** Game window */
	Window window_;

	/** Game world */
	World world_;

	/** Player */
	Snake snake_;

	/* Time since last tick */
	float tickCounter_;

#pragma region Technical
	/** Last tick value. Time from game start. */
	Uint32 lastTick_;

	/** Time since last tick */
	Uint32 dt_;

	/** Event to log user inputs */
	SDL_Event event_;

	/** Game quits when true */
	bool isDone_;
#pragma endregion

};