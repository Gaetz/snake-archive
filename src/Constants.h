#pragma once

/// Singleton config
class Constants {
public:
	static Constants* get();
	const int getScreenWidth() const;
	const int getScreenHeight() const;
	const int getBlockSize() const;
	const int getTextBoxX() const;
	const int getCharSize() const;
	const int getBaseSpeed() const;
	const int getBonusMinumumTime() const;
	const int getBonusDistanceTime() const;

private:
	static Constants *instance;
	Constants();
	void initialize();
	int screenWidth;
	int screenHeight;
	int blockSize;
	int textBoxX;
	int charSize;
	int baseSpeed;
	int bonusMinimumTime;
	int bonusDistanceTime;
};