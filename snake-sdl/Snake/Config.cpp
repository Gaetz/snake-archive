#include "Config.h"

Config *Config::instance = nullptr;

Config::Config()
{
	screenWidth_ = 330;
	screenHeight_ = 600;
	blockSize_ = 15;
	textBoxX_ = 218;
	charSize_ = 30;
	baseSpeed_ = 15;
	bonusMinimumTime_ = 25;
	bonusDistanceTime_ = 10;
	// Colors
	black_.r = 0;
	black_.g = 0;
	black_.b = 0;
	black_.a = 255;
	grey_.r = 90;
	grey_.g = 90;
	grey_.b = 90;
	grey_.a = 255;
	green_.r = 80;
	green_.g = 120;
	green_.b = 80;
	green_.a = 255;
}

Config * Config::Get()
{
	if (!instance) {
		instance = new Config;
	}
	return instance;
}

const int Config::GetScreenWidth() const
{
	return screenWidth_;
}

const int Config::GetScreenHeight() const
{
	return screenHeight_;
}

const int Config::GetBlockSize() const
{
	return blockSize_;
}

const int Config::GetTextBoxX() const
{
	return textBoxX_;
}

const int Config::GetCharSize() const
{
	return charSize_;
}

const int Config::GetBaseSpeed() const
{
	return baseSpeed_;
}

const int Config::GetBonusMinumumTime() const
{
	return bonusMinimumTime_;
}

const int Config::GetBonusDistanceTime() const
{
	return bonusDistanceTime_;
}

const SDL_Color Config::ColorBlack() const
{
	return black_;
}

const SDL_Color Config::ColorGrey() const
{
	return grey_;
}

const SDL_Color Config::ColorGreen() const
{
	return green_;
}
