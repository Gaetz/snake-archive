#pragma once
#include <SFML\Graphics.hpp>
#include "Constants.h"
#include "Snake.h"

class Apple
{
public:
	Apple();

	const sf::Vector2i getPosition() const;
	const bool isBonus() const;

	void respawn(sf::Vector2i position, sf::Vector2i playerPosition);
	void tick(Snake &player);
	void draw(sf::RenderWindow &window);

private:
	sf::CircleShape mBonusShape;
	sf::CircleShape mNormalShape;
	sf::Vector2i mPosition;
	bool mIsBonus;
	int mBonusTime;
	int mBlockSize;
	int mTimeLimit;

	void drawBonus(sf::RenderWindow &window);
	void drawNormal(sf::RenderWindow &window);
};