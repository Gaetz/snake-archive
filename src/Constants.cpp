#include "Constants.h"

Constants *Constants::instance = nullptr;

Constants::Constants()
{

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
