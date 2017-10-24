#include "Game.h"

Game::Game() : mWindow("Snake", sf::Vector2u(Constants::get()->getScreenWidth(), Constants::get()->getScreenHeight())),
               mSnake(mWorld.getBlockSize(), &mTextbox),
               mWorld(sf::Vector2u(Constants::get()->getScreenWidth(), Constants::get()->getScreenWidth()))
{
    mClock.restart();
    srand(time(NULL));
	// Dependancy injection
	mWorld.reset(mSnake);
	// Background
	int screenWidth = Constants::get()->getScreenWidth();
	int screenHeight = Constants::get()->getScreenHeight();
    mBackground.setSize(sf::Vector2f(screenWidth, screenHeight - screenWidth));
    mBackground.setFillColor(sf::Color::Black);
    mBackground.setPosition(sf::Vector2f(0, screenWidth));
	mPointDisplay = PointDisplay();
	// Sound
	if (!mMusic.openFromFile("assets/sornettes.ogg"))
		std::cout << "Could not load music: assets/sornettes.ogg" << std::endl;
	mMusic.play();
	if (!mSoundCollision.loadFromFile("assets/mort_2.ogg"))
		std::cout << "Could not load music: assets/mort_2.ogg" << std::endl;
	if (!mSoundHiScore.loadFromFile("assets/hi-score.ogg"))
		std::cout << "Could not load music: assets/hi-score.ogg" << std::endl;
	if (!mSoundTurn.loadFromFile("assets/tourner.ogg"))
		std::cout << "Could not load music: assets/tourner.ogg" << std::endl;
	// Data
    mTextbox.setup(5, Constants::get()->getCharSize(), Constants::get()->getTextBoxX(), sf::Vector2f(mWorld.getBlockSize(), screenWidth));
    mElapsed = 0.0f;
	mHiScore = 0;
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && mSnake.getPhysicalDirection() != Direction::Down && mSnake.getPhysicalDirection() != Direction::Up)
    {
        mSnake.setDirection(Direction::Up);
		playTurnSound();
    }
    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && mSnake.getPhysicalDirection() != Direction::Up && mSnake.getPhysicalDirection() != Direction::Down) 
		|| (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && mSnake.getDirection() == Direction::None))
    {
        mSnake.setDirection(Direction::Down);
		playTurnSound();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && mSnake.getPhysicalDirection() != Direction::Right && mSnake.getPhysicalDirection() != Direction::Left)
    {
        mSnake.setDirection(Direction::Left);
		playTurnSound();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && mSnake.getPhysicalDirection() != Direction::Left && mSnake.getPhysicalDirection() != Direction::Right)
    {
        mSnake.setDirection(Direction::Right);
		playTurnSound();
    }
}

void Game::playTurnSound()
{
	mSound.setBuffer(mSoundTurn);
	mSound.play();
}

void Game::update()
{
    mWindow.update();
	mPointDisplay.update();

    float timestep = 1.0f / mSnake.getSpeed();
    if (mElapsed >= timestep)
    {
        mSnake.tick();
        mWorld.update(mSnake, mPointDisplay);
        mElapsed -= timestep;

        if (mSnake.hasLost())
        {
			mWorld.reset(mSnake);
            if (mSnake.getScore() > mHiScore)
            {
                mHiScore = mSnake.getScore();
				mSound.setBuffer(mSoundHiScore);
				mSound.play();
            }
			else
			{
				mSound.setBuffer(mSoundCollision);
				mSound.play();
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
	mPointDisplay.render(*mWindow.getRenderWindow());

    mTextbox.render(*mWindow.getRenderWindow());

    mWindow.endDraw();
}

void Game::restartClock()
{
    mElapsed += mClock.restart().asSeconds();
}