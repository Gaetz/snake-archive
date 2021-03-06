#include "Textbox.h"

Textbox::Textbox()
{
    setup(5, 9, 200, sf::Vector2f(0, 0));
}

Textbox::Textbox(int visible, int charSize, int width, sf::Vector2f screenPosition)
{
    setup(visible, charSize, width, screenPosition);
}

Textbox::~Textbox()
{
    clear();
}

void Textbox::setup(int visible, int charSize, int width, sf::Vector2f screenPosition)
{
    mNumVisible = visible;

    // Offset for content display in window
    sf::Vector2f offset(2.0f, 2.0f);

    mFont.loadFromFile("assets/Famirids..ttf");
    mContent.setFont(mFont);
    mContent.setString("");
    mContent.setCharacterSize(charSize);
    mContent.setFillColor(sf::Color(165, 212, 40));
    mContent.setOutlineColor(sf::Color(165, 212, 40));
    mContent.setPosition(screenPosition + offset);

    mBackdrop.setSize(sf::Vector2f(width, (visible * (charSize * 1.2f))));
    mBackdrop.setFillColor(sf::Color(90, 90, 90, 0));
    mBackdrop.setPosition(screenPosition);

    clear();
    add("> Score: 0");
}

void Textbox::add(std::string message)
{
    mMessages.push_back(message);
    if (mMessages.size() < 3)
        return;
    mMessages.erase(mMessages.begin());
}

void Textbox::clear()
{
    mMessages.clear();
}

void Textbox::render(sf::RenderWindow &window)
{
    std::string content;
    // Append messages with a end of line
    for (auto &itr : mMessages)
    {
        content.append(itr + "\n");
    }
    // Display content
    if (content != "")
    {
        mContent.setString(content);
        window.draw(mBackdrop);
        window.draw(mContent);
    }
}