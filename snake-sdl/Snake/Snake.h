#pragma once
#include <vector>
#include <iostream>
//#include "Textbox.h"
#include "Config.h"
#include "Window.h"
#include "RectangleShape.h"
#include "World.h"

//#include "PointDisplay.h"
#include "Vector2.hpp"


struct SnakeSegment
{
	SnakeSegment(Uint16 x, Uint16 y) : position(x, y) {}
	utils::Vector2i16 position;
};

using SnakeContainer = std::vector<SnakeSegment>;

enum class Direction
{
	None,
	Up,
	Down,
	Left,
	Right
};

class Snake
{
public:
	Snake(World* world);
	~Snake();

	const Direction GetDirection();
	const void SetDirection(Direction dir);
	const int GetSpeed();
	const utils::Vector2i16 GetPosition();
	const int GetLives();
	const int GetScore();
	//void IncreaseScore(bool bonus, PointDisplay& display);
	bool HasLost();

	/// Returns the direciton the snake is facing
	Direction GetPhysicalDirection();

	/// Handle losing
	void Lose();

	/// Invert loss status
	void ToggleLose();

	/// Cancel bonus
	void CancelBonus();

	/// Make the snake grow
	void Extend();

	/// Reset snake to starting position
	void Reset();

	/// Movement method
	void Move();

	/// Update method
	void Tick();

	/// Draw snake in window
	void Render(Window& window);

private:
	/// Segment vector
	SnakeContainer snakeBody_;

	/** Reference to world */
	World* world_;

	/// Size of the graphics
	int size_;

	/// Current direction
	Direction dir_;

	/// Snake speed
	int speed_;

	/// Lives
	int lives_;

	/// Score
	int score_;

	/// Losing state
	bool lost_;

	/// Log system
	//Textbox* log_;

	/// Shape used in rendering
	gfx::RectangleShape bodyRect_;

	/// Score multiplier when eating successive bonus apples
	int bonusMultiplier_;

	//sf::SoundBuffer soundGrey_;
	//sf::SoundBuffer soundBlack0_;
	//sf::SoundBuffer soundBlack1_;
	//sf::SoundBuffer soundBlack2_;
	//sf::Sound sound_;

	/// Checking for collisions with itself
	void CheckAutoCollision();

	/** Check collision with world bounds */
	void CheckWallCollision();

	/// Play a sound
	//void PlaySound(sf::SoundBuffer& sb);
};