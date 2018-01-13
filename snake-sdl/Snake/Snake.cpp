#pragma once
#include "Snake.h"

using utils::Vector2i16;

Snake::Snake(World* world) : world_(world)
{
	size_ = Config::Get()->GetBlockSize();
	bodyRect_.SetWidth(size_ - 1);
	bodyRect_.SetHeight(size_ - 1);
	Reset();
}

Snake::~Snake()
{

}

const Direction Snake::GetDirection() { return dir_; };
const void Snake::SetDirection(Direction dir) { dir_ = dir; }
const int Snake::GetSpeed() { return speed_; };
const int Snake::GetLives() { return lives_; };
const int Snake::GetScore() { return score_; };
bool Snake::HasLost() { return lost_; }
void Snake::Lose() { lost_ = true; }
void Snake::ToggleLose() { lost_ = !lost_; }

const Vector2i16 Snake::GetPosition()
{
	return (!snakeBody_.empty() ? snakeBody_.front().position : Vector2i16(1, 1));
}

Direction Snake::GetPhysicalDirection()
{
	if (snakeBody_.size() <= 1)
	{
		return Direction::None;
	}

	SnakeSegment &head = snakeBody_[0];
	SnakeSegment &neck = snakeBody_[1];
	if (head.position.x == neck.position.x)
	{
		return (head.position.y > neck.position.y ? Direction::Down : Direction::Up);
	}
	else if (head.position.y == neck.position.y)
	{
		return (head.position.x > neck.position.x ? Direction::Right : Direction::Left);
	}
	return Direction::Down;
}

void Snake::Reset()
{
	snakeBody_.clear();

	snakeBody_.push_back(SnakeSegment(5, 7));
	snakeBody_.push_back(SnakeSegment(5, 6));
	snakeBody_.push_back(SnakeSegment(5, 5));

	SetDirection(Direction::None); // Start still
	speed_ = Config::Get()->GetBaseSpeed();
	lives_ = 1;
	score_ = 0;
	lost_ = false;
	bonusMultiplier_ = 1;
}

void Snake::Tick()
{
	if (snakeBody_.empty())
		return;
	if (dir_ == Direction::None)
		return;
	Move();
	CheckAutoCollision();
	CheckWallCollision();
}

void Snake::Move()
{
	// Move following segments to the next segment position
	for (SnakeContainer::size_type i = snakeBody_.size() - 1; i > 0; --i)
	{
		snakeBody_[i].position = snakeBody_[i - 1].position;
	}
	// Move head
	if (dir_ == Direction::Up)
	{
		--snakeBody_[0].position.y;
	}
	else if (dir_ == Direction::Down)
	{
		++snakeBody_[0].position.y;
	}
	else if (dir_ == Direction::Left)
	{
		--snakeBody_[0].position.x;
	}
	else if (dir_ == Direction::Right)
	{
		++snakeBody_[0].position.x;
	}
}

void Snake::CheckAutoCollision()
{
	if (snakeBody_.size() < 5)
		return;
	SnakeSegment &head = snakeBody_.front();
	for (auto itr = snakeBody_.begin() + 1; itr != snakeBody_.end(); ++itr)
	{
		if (itr->position == head.position)
		{
			Lose();
			break;
		}
	}
}

void Snake::CheckWallCollision()
{
	// Player lose when hitting bounds
	Uint16 gridSizeX = world_->GetBoardSize().x / Config::Get()->GetBlockSize();
	Uint16 gridSizeY = world_->GetBoardSize().y / Config::Get()->GetBlockSize();
	if (GetPosition().x <= 0 ||
		GetPosition().y <= 0 ||
		GetPosition().x >= gridSizeX - 1 ||
		GetPosition().y >= gridSizeY - 1)
	{
		Lose();
	}
}

void Snake::Render(Window& window) {
	if (snakeBody_.empty())
		return;

	// Draw head
	auto head = snakeBody_.begin();
	bodyRect_.SetColor(Config::Get()->ColorBlack());
	bodyRect_.SetPosition(Vector2i16(head->position.x * size_, head->position.y * size_));
	bodyRect_.Render(window);

	// Draw body
	bodyRect_.SetColor(Config::Get()->ColorGrey());
	for (auto itr = snakeBody_.begin() + 1; itr != snakeBody_.end(); ++itr)
	{
		bodyRect_.SetPosition(Vector2i16(itr->position.x * size_, itr->position.y * size_));
		bodyRect_.Render(window);
	}
}

