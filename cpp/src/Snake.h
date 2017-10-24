#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include "Textbox.h"
#include "Constants.h"
#include "PointDisplay.h"

struct SnakeSegment
{
    SnakeSegment(int x, int y) : position(x, y) {}
    sf::Vector2i position;
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
    Snake(int blockSize, Textbox* log);
    ~Snake();

	const Direction getDirection();
	const void setDirection(Direction dir);
	const int getSpeed();
    const sf::Vector2i getPosition();
	const int getLives();
	const int getScore();
    void increaseScore(bool bonus, PointDisplay& display);
    bool hasLost();

    /// Returns the direciton the snake is facing
    Direction getPhysicalDirection();

    /// Handle losing
    void lose();

    /// Invert loss status
    void toggleLose();

	/// Cancel bonus
	void cancelBonus();

    /// Make the snake grow
    void extend();

    /// Reset snake to starting position
    void reset();

    /// Movement method
    void move();

    /// Update method
    void tick();

    /// Cut a number of the snake's segments
    void cut(int segments);

    /// Draw snake in window
    void render(sf::RenderWindow &window);

  private:
    /// Segment vector
    SnakeContainer mSnakeBody;

    /// Size of the graphics
    int mSize;

    /// Current direction
    Direction mDir;

    /// Snake speed
    int mSpeed;

    /// Lives
    int mLives;

    /// Score
    int mScore;

    /// Losing state
    bool mLost;
    /// Log system
    Textbox* mLog;

    /// Shape used in rendering
    sf::RectangleShape mBodyRect;

	/// Score multiplier when eating successive bonus apples
	int mBonusMultiplier;

	sf::SoundBuffer mSoundGrey;
	sf::SoundBuffer mSoundBlack0;
	sf::SoundBuffer mSoundBlack1;
	sf::SoundBuffer mSoundBlack2;
	sf::Sound mSound;

    /// Checking for collisions
    void checkCollision();

	/// Play a sound
	void playSound(sf::SoundBuffer& sb);
};