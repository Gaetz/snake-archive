#include "World.h"

World::World(sf::Vector2u windowSize)
{
    mBlockSize = Constants::get()->getBlockSize();
    mWindowSize = windowSize;
	mApple = Apple();
	respawnApple();

    // Draw bounds
    for (int i = 0; i < 4; ++i)
    {
        mBounds[i].setFillColor(sf::Color::Black);
        if (!((i + 1) % 2))
        {
            mBounds[i].setSize(sf::Vector2f(mWindowSize.x, mBlockSize));
        }
        else
        {
            mBounds[i].setSize(sf::Vector2f(mBlockSize, mWindowSize.y));
        }
        if (i < 2)
        {
            mBounds[i].setPosition(0, 0);
        }
        else
        {
            mBounds[i].setOrigin(mBounds[i].getSize());
            mBounds[i].setPosition(sf::Vector2f(mWindowSize));
        }
    }
}

World::~World(){};

int World::getBlockSize() { return mBlockSize; }

void World::reset() {
	mApple.reset();
}

void World::respawnApple()
{
    int maxX = (mWindowSize.x / mBlockSize) - 2;
    int maxY = (mWindowSize.y / mBlockSize) - 2;
	mApple.respawn(sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1));
}

void World::update(Snake &player)
{
	mApple.tick(player);
    // Apple eating
    if (player.getPosition() == mApple.getPosition())
    {
        player.extend();
        player.increaseScore(mApple.isBonus());
        respawnApple();
    }

    // Player lose when hitting bounds
    int gridSizeX = mWindowSize.x / mBlockSize;
    int gridSizeY = mWindowSize.y / mBlockSize;
    if (player.getPosition().x <= 0 ||
        player.getPosition().y <= 0 ||
        player.getPosition().x >= gridSizeX - 1 ||
        player.getPosition().y >= gridSizeY - 1)
    {
        player.lose();
    }
}

void World::render(sf::RenderWindow &window)
{
    for (int i = 0; i < 4; ++i)
    {
        window.draw(mBounds[i]);
    }
    mApple.draw(window);
}