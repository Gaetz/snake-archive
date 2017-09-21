#include "Constants.h"

Constants *Constants::instance = nullptr;

Constants::Constants()
{
	initialize();
}

void Constants::initialize() {
	screenWidth = 440;
	screenHeight = 800;
	blockSize = 20;
	textBoxX = 218;
	charSize = 30;
	baseSpeed = 15;
	bonusTime = 25;
}

Constants * Constants::get()
{
	if (!instance) {
		instance = new Constants;
	}
	return instance;
}

const int Constants::getScreenWidth() const
{
	return screenWidth;
}

const int Constants::getScreenHeight() const
{
	return screenHeight;
}

const int Constants::getBlockSize() const
{
	return blockSize;
}

const int Constants::getTextBoxX() const
{
	return textBoxX;
}

const int Constants::getCharSize() const
{
	return charSize;
}

const int Constants::getBaseSpeed() const
{
	return baseSpeed;
}

const int Constants::getBonusTime() const
{
	return bonusTime;
}
