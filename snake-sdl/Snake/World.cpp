#include "World.h"

using utils::Vector2u16;

World::World(const Vector2u16& boardSize)
{
	blockSize_ = Config::Get()->GetBlockSize();
	boardSize_ = boardSize;

	SDL_Rect bgRect;
	bgRect.x = 0;
	bgRect.y = 0;
	bgRect.w = boardSize.x;
	bgRect.h = boardSize.y;

	background_ = gfx::RectangleShape(bgRect, Config::Get()->ColorGreen());

	// Draw bounds
	for (int i = 0; i < 4; ++i)
	{
		// Rectangles sizes
		if (!((i + 1) % 2))
		{
			bounds_[i].w = blockSize_;
			bounds_[i].h = boardSize_.y;
		}
		else
		{
			bounds_[i].w = boardSize_.x;
			bounds_[i].h = blockSize_;
		}
		// Rectangles positions
		if (i < 2)
		{
			bounds_[i].x = 0;
			bounds_[i].y = 0;
		}
		else if(i == 2)
		{
			bounds_[i].x = 0;
			bounds_[i].y = boardSize_.y - blockSize_;
		}
		else if (i == 3)
		{
			bounds_[i].x = boardSize_.x - blockSize_;
			bounds_[i].y = 0;
		}
	}
}

World::~World() {}
const utils::Vector2u16 World::GetBoardSize()
{
	return boardSize_;
}
;

void World::Render(Window& window)
{
	background_.Render(window);
	for (int i = 0; i < 4; ++i)
	{
		window.DrawRect(&bounds_[i], 0, 0, 0, 255, true);
	}
}