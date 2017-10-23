#include "Apple.h"

Apple::Apple()
{
	mBlockSize = Constants::get()->getBlockSize();

	mBonusShape.setFillColor(sf::Color::Black);
	mBonusShape.setRadius(mBlockSize / 2);
	mNormalShape.setFillColor(sf::Color(80, 120, 80));
	mNormalShape.setRadius(mBlockSize / 2);
}

const sf::Vector2i Apple::getPosition() const
{
	return mPosition;
}

const bool Apple::isBonus() const
{
	return mIsBonus;
}

void Apple::tick(Snake &player)
{
	if (player.getDirection() != Direction::None) {
		if (mBonusTime <= mTimeLimit) {
			++mBonusTime;
		}
		else {
			player.cancelBonus();
			mIsBonus = false;
		}
	}
}

void Apple::respawn(sf::Vector2i position, sf::Vector2i playerPosition)
{
	// New position
	mPosition = position;
	mBonusShape.setPosition(position.x * mBlockSize, position.y * mBlockSize);
	mNormalShape.setPosition(position.x * mBlockSize, position.y * mBlockSize);
	// Bonus time computing
	int distance = abs(position.x - playerPosition.x) + abs(position.y - playerPosition.y);
	mIsBonus = true;
	mBonusTime = 0;
	mTimeLimit = distance <= 25 ? 
		Constants::get()->getBonusMinumumTime() : 
		distance + Constants::get()->getBonusDistanceTime();
}

void Apple::reset() {
	mIsBonus = true;
	mBonusTime = 0;
}

void Apple::draw(sf::RenderWindow &window)
{
	if (mIsBonus) {
		drawBonus(window);
	}
	else {
		drawNormal(window);
	}
}

void Apple::drawBonus(sf::RenderWindow &window)
{
	window.draw(mBonusShape);
}

void Apple::drawNormal(sf::RenderWindow &window)
{
	window.draw(mNormalShape);
}
