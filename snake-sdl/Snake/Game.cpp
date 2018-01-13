#include "Game.h"

Game::Game() :
	window_("Snake, Hard Mode", Config::Get()->GetScreenWidth(), Config::Get()->GetScreenHeight()),
	world_(utils::Vector2u16(Config::Get()->GetScreenWidth(), Config::Get()->GetScreenWidth())),
	snake_(&world_)
{
	isDone_ = false;
	srand((unsigned int)time(NULL));


}

Game::~Game() {
	window_.~Window();
}

bool Game::IsDone() {
	return isDone_;
}

void Game::HandleInput() {
	while (SDL_PollEvent(&event_) != 0)
	{
		if (event_.type == SDL_QUIT)
		{
			isDone_ = true;
		}
		else if (event_.type == SDL_KEYDOWN) {
			// Key up
			if (event_.key.keysym.sym == SDLK_UP
				&& snake_.GetPhysicalDirection() != Direction::Down
				&& snake_.GetPhysicalDirection() != Direction::Up) 
			{
				snake_.SetDirection(Direction::Up);
			}
			// Key down
			else if (((event_.key.keysym.sym == SDLK_DOWN) 
					&& snake_.GetPhysicalDirection() != Direction::Up 
					&& snake_.GetPhysicalDirection() != Direction::Down)
				// Handle start case
					|| (event_.key.keysym.sym == SDLK_DOWN && snake_.GetDirection() == Direction::None))
			{
				snake_.SetDirection(Direction::Down);
			}
			// Key left
			if (event_.key.keysym.sym == SDLK_LEFT 
				&& snake_.GetPhysicalDirection() != Direction::Right
				&& snake_.GetPhysicalDirection() != Direction::Left)
			{
				snake_.SetDirection(Direction::Left);
			}
			// Key right
			if (event_.key.keysym.sym == SDLK_RIGHT
				&& snake_.GetPhysicalDirection() != Direction::Right
				&& snake_.GetPhysicalDirection() != Direction::Left)
			{
				snake_.SetDirection(Direction::Right);
			}
		}
	}
}


void Game::Update() {
	window_.Update();

	float timestep = 1000.0f / snake_.GetSpeed();

	tickCounter_ += dt_;
	if (tickCounter_ >= timestep)
	{
		snake_.Tick();
		tickCounter_ -= timestep;

		if (snake_.HasLost())
		{
			snake_.Reset();
		}
	}
}

void Game::Render() {
	window_.BeginDraw();

	// Draw game objects
	world_.Render(window_);
	snake_.Render(window_);

	window_.EndDraw();
}

void Game::ManageTime() {
	Uint32 currentTick = SDL_GetTicks();
	dt_ = currentTick - lastTick_;
	lastTick_ = currentTick;
}