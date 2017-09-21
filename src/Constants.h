#pragma once

/// Singleton config
class Constants {

private:
	static Constants *instance;
	Constants();
	const int screenWidth = 440;
	const int screenHeight = 800;
	const int blockSize = 20;
	const int textBoxX = 218;
	const int charSize = 30;
	const int baseSpeed = 15;

public:
	static Constants* get();
	const int getScreenWidth() const;
	const int getScreenHeight() const;
	const int getBlockSize() const;
	const int getTextBoxX() const;
	const int getCharSize() const;
	const int getBaseSpeed() const;
};