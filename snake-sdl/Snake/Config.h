#pragma once

#include <SDL.h>

/// Singleton config
class Config {
public:
	static Config* Get();
	const int GetScreenWidth() const;
	const int GetScreenHeight() const;
	const int GetBlockSize() const;
	const int GetTextBoxX() const;
	const int GetCharSize() const;
	const int GetBaseSpeed() const;
	const int GetBonusMinumumTime() const;
	const int GetBonusDistanceTime() const;
	const SDL_Color ColorBlack() const;
	const SDL_Color ColorGrey() const;
	const SDL_Color ColorGreen() const;

private:
	static Config *instance;

	Config();

	int screenWidth_;
	int screenHeight_;
	int blockSize_;
	int textBoxX_;
	int charSize_;
	int baseSpeed_;
	int bonusMinimumTime_;
	int bonusDistanceTime_;
	SDL_Color black_;
	SDL_Color grey_;
	SDL_Color green_;
};