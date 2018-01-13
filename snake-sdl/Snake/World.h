#pragma once
#include "SDL.h"

#include "Config.h"
#include "Window.h"
#include "Vector2.hpp"
#include "RectangleShape.h"

class World {
public:
	World(const utils::Vector2u16& boardSize);
	~World();

	const utils::Vector2u16 GetBoardSize();

	/// Update
	//void Update(Snake &player, PointDisplay& pointDisplay);

	/// Make an apple appear
	//void RespawnApple(Snake& player);

	/// Reset world when player lose
	//void Reset(Snake& player);

	/// Draw world in window
	void Render(Window& window);

private:
	utils::Vector2u16 boardSize_;

	SDL_Rect bounds_[4];
	int blockSize_;
	gfx::RectangleShape background_;
	//Apple mApple;
};

