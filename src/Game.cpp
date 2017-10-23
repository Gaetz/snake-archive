#include "Game.h"

Game::Game() : mWindow("Snake", sf::Vector2u(Constants::get()->getScreenWidth(), Constants::get()->getScreenHeight())),
               mSnake(mWorld.getBlockSize(), &mTextbox),
               mWorld(sf::Vector2u(Constants::get()->getScreenWidth(), Constants::get()->getScreenWidth()), mSnake)
{
    mClock.restart();
    srand(time(NULL));
    mHiScore = 0;
	int screenWidth = Constants::get()->getScreenWidth();
	int screenHeight = Constants::get()->getScreenHeight();
    mBackground.setSize(sf::Vector2f(screenWidth, screenHeight - screenWidth));
    mBackground.setFillColor(sf::Color::Black);
    mBackground.setPosition(sf::Vector2f(0, screenWidth));

    mTextbox.setup(5, Constants::get()->getCharSize(), Constants::get()->getTextBoxX(), sf::Vector2f(mWorld.getBlockSize(), screenWidth));
    mElapsed = 0.0f;
}

Game::~Game()
{
}

const Window &Game::getWindow() const
{
    return this->mWindow;
}

sf::Time Game::getElapsed() const
{
    return mClock.getElapsedTime();
}

void Game::handleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && mSnake.getPhysicalDirection() != Direction::Down)
    {
        mSnake.setDirection(Direction::Up);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && mSnake.getPhysicalDirection() != Direction::Up)
    {
        mSnake.setDirection(Direction::Down);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && mSnake.getPhysicalDirection() != Direction::Right)
    {
        mSnake.setDirection(Direction::Left);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && mSnake.getPhysicalDirection() != Direction::Left)
    {
        mSnake.setDirection(Direction::Right);
    }
}

void Game::update()
{
    mWindow.update();

    float timestep = 1.0f / mSnake.getSpeed();
    if (mElapsed >= timestep)
    {
        mSnake.tick();
        mWorld.update(mSnake);
        mElapsed -= timestep;

        if (mSnake.hasLost())
        {
			mWorld.reset(mSnake);
            if (mSnake.getScore() > mHiScore)
            {
                mHiScore = mSnake.getScore();
            }
            mTextbox.clear();
            mTextbox.add("> GAME OVER. Score: " + std::to_string(mSnake.getScore()));
            mTextbox.add("> Hi: " + std::to_string(mHiScore));            
            mSnake.reset();
        }
    }
}

void Game::render()
{
    mWindow.beginDraw();

    mWorld.render(*mWindow.getRenderWindow());
    mSnake.render(*mWindow.getRenderWindow());
    mWindow.draw(mBackground);
    mTextbox.render(*mWindow.getRenderWindow());

    mWindow.endDraw();
}

void Game::restartClock()
{
    mElapsed += mClock.restart().asSeconds();
}