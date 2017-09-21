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

	void respawn(sf::Vector2i position);
	void reset();
	void tick(Direction direction);
	void draw(sf::RenderWindow &window);

private:
	sf::CircleShape mBonusShape;
	sf::CircleShape mNormalShape;
	sf::Vector2i mPosition;
	bool mIsBonus;
	int mBonusTime;
	int mBlockSize;

	void drawBonus(sf::RenderWindow &window);
	void drawNormal(sf::RenderWindow &window);
};