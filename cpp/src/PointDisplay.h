#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Constants.h"

class PointDisplay
{
public:
	PointDisplay();
	~PointDisplay();

	/// Setup text box
	void setup(int value, int charSize, int width, sf::Vector2f screenPosition);

	/// Clear textbox
	void clear();

	/// Update state
	void update();

	/// Draw display
	void render(sf::RenderWindow &window);

private:
	sf::Font mFont;
	sf::Text mContent;
	sf::Uint8 mOpacity;
};