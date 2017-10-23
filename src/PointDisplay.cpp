#include "PointDisplay.h"

PointDisplay::PointDisplay()
{
	mFont.loadFromFile("assets/Famirids..ttf");
	mContent.setFont(mFont);
	mContent.setString("");
	mOpacity = 0;
	mContent.setCharacterSize(10);
	mContent.setFillColor(sf::Color(90, 90, 90));
	mContent.setOutlineColor(sf::Color(90, 90, 90));
	mContent.setPosition(sf::Vector2f(100.0f, 100.0f));
}

PointDisplay::~PointDisplay()
{
	clear();
}

void PointDisplay::setup(int value, int charSize, int width, sf::Vector2f snakePosition)
{
	clear();
	mOpacity = 255;
	mFont.loadFromFile("assets/Famirids..ttf");
	mContent.setFont(mFont);
	mContent.setString(sf::String(std::to_string(value)));
	mContent.setCharacterSize(charSize);
	mContent.setFillColor(sf::Color(0, 0, 0));
	mContent.setOutlineColor(sf::Color(0, 0, 0));
	mContent.setPosition(snakePosition + sf::Vector2f(0, - Constants::get()->getBlockSize()));
}

void PointDisplay::clear()
{
	mContent.setString("");
}

void PointDisplay::update()
{
	if (mOpacity > 0 && mContent.getString() != "")
	{
		mContent.setFillColor(sf::Color(0, 0, 0, mOpacity));
		mContent.setOutlineColor(sf::Color(0, 0, 0, mOpacity));
		mOpacity = mOpacity - 5;
		sf::Vector2f newPosition = mContent.getPosition() + sf::Vector2f(0, -0.5f);
		mContent.setPosition(newPosition);
	}
}

void PointDisplay::render(sf::RenderWindow &window)
{
	if(mContent.getString() != "")
		window.draw(mContent);
}