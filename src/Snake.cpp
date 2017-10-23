#include "Snake.h"

Snake::Snake(int blockSize, Textbox *log)
{
    mSize = blockSize;
    mLog = log;
    mBodyRect.setSize(sf::Vector2f(mSize - 1, mSize - 1)); // Separate segments with 1 pixel
    reset();
}

Snake::~Snake() {}

void Snake::reset()
{
    mSnakeBody.clear();

    mSnakeBody.push_back(SnakeSegment(5, 7));
    mSnakeBody.push_back(SnakeSegment(5, 6));
    mSnakeBody.push_back(SnakeSegment(5, 5));

    setDirection(Direction::None); // Start still
    mSpeed = Constants::get()->getBaseSpeed();
    mLives = 1;
    mScore = 0;
    mLost = false;
	mBonusMultiplier = 1;
}

const Direction Snake::getDirection() { return mDir; };
const void Snake::setDirection(Direction dir) { mDir = dir; }
const int Snake::getSpeed() { return mSpeed; };
const int Snake::getLives() { return mLives; };
const int Snake::getScore() { return mScore; };
bool Snake::hasLost() { return mLost; }
void Snake::lose() { mLost = true; }
void Snake::toggleLose() { mLost = !mLost; }

const sf::Vector2i Snake::getPosition()
{
    return (!mSnakeBody.empty() ? mSnakeBody.front().position : sf::Vector2i(1, 1));
}

void Snake::increaseScore(bool bonus, PointDisplay& display)
{
	if (!bonus) {
		mBonusMultiplier = 1;
	}
	display.setup(mBonusMultiplier, 30, 200, sf::Vector2f(getPosition().x * Constants::get()->getBlockSize(), getPosition().y  * Constants::get()->getBlockSize()));
    mScore += mBonusMultiplier;
	if (bonus) {
		++mBonusMultiplier;
	}
    mLog->clear();
    mLog->add("> Score: " + std::to_string(mScore));
	if (mBonusMultiplier > 1) {
		mLog->add("> Bonus: x" + std::to_string(mBonusMultiplier));
	}
}

void Snake::cancelBonus() {
	mLog->clear();
	mLog->add("> Score: " + std::to_string(mScore));
}

Direction Snake::getPhysicalDirection()
{
    if (mSnakeBody.size() <= 1)
    {
        return Direction::None;
    }

    SnakeSegment &head = mSnakeBody[0];
    SnakeSegment &neck = mSnakeBody[1];
    if (head.position.x == neck.position.x)
    {
        return (head.position.y > neck.position.y ? Direction::Down : Direction::Up);
    }
    else if (head.position.y == neck.position.y)
    {
        return (head.position.x > neck.position.x ? Direction::Right : Direction::Left);
    }
    return Direction::None;
}

void Snake::extend()
{
    if (mSnakeBody.empty())
    {
        return;
    }

    // Last snake segment
    SnakeSegment &tailHead = mSnakeBody[mSnakeBody.size() - 1];
    // More than one segment case
    if (mSnakeBody.size() > 1)
    {
        // Next to last segment
        SnakeSegment &tailBone = mSnakeBody[mSnakeBody.size() - 2];
        if (tailHead.position.x == tailBone.position.x)
        {
            if (tailHead.position.y > tailBone.position.y)
            {
                mSnakeBody.push_back(SnakeSegment(tailHead.position.x, tailHead.position.y + 1));
            }
            else
            {
                mSnakeBody.push_back(SnakeSegment(tailHead.position.x, tailHead.position.y - 1));
            }
        }
        else if (tailHead.position.y == tailBone.position.y)
        {
            if (tailHead.position.x > tailBone.position.x)
            {
                mSnakeBody.push_back(SnakeSegment(tailHead.position.x + 1, tailHead.position.y));
            }
            else
            {
                mSnakeBody.push_back(SnakeSegment(tailHead.position.x - 1, tailHead.position.y));
            }
        }
    }
    // One segment case
    else
    {
        if (mDir == Direction::Up)
        {
            mSnakeBody.push_back(SnakeSegment(tailHead.position.x, tailHead.position.y + 1));
        }
        else if (mDir == Direction::Down)
        {
            mSnakeBody.push_back(SnakeSegment(tailHead.position.x, tailHead.position.y - 1));
        }
        else if (mDir == Direction::Left)
        {
            mSnakeBody.push_back(SnakeSegment(tailHead.position.x + 1, tailHead.position.y));
        }
        else if (mDir == Direction::Right)
        {
            mSnakeBody.push_back(SnakeSegment(tailHead.position.x - 1, tailHead.position.y));
        }
    }
}

void Snake::tick()
{
    if (mSnakeBody.empty())
        return;
    if (mDir == Direction::None)
        return;
    move();
    checkCollision();
}

void Snake::move()
{
    // Move following segments to the next segment position
    for (int i = mSnakeBody.size() - 1; i > 0; --i)
    {
        mSnakeBody[i].position = mSnakeBody[i - 1].position;
    }
    // Move head
    if (mDir == Direction::Up)
    {
        --mSnakeBody[0].position.y;
    }
    else if (mDir == Direction::Down)
    {
        ++mSnakeBody[0].position.y;
    }
    else if (mDir == Direction::Left)
    {
        --mSnakeBody[0].position.x;
    }
    else if (mDir == Direction::Right)
    {
        ++mSnakeBody[0].position.x;
    }
}

void Snake::checkCollision()
{
    if (mSnakeBody.size() < 5)
        return;
    SnakeSegment &head = mSnakeBody.front();
    for (auto itr = mSnakeBody.begin() + 1; itr != mSnakeBody.end(); ++itr)
    {
        if (itr->position == head.position)
        {
            int segments = mSnakeBody.end() - itr;
            cut(segments);
            break;
        }
    }
}

void Snake::cut(int segments)
{
    for (int i = 0; i < segments; i++)
    {
        mSnakeBody.pop_back();
    }
    --mLives;
    if (!mLives)
    {
        lose();
        return;
    }
}

void Snake::render(sf::RenderWindow &window)
{
    if (mSnakeBody.empty())
        return;

    // Draw head
    auto head = mSnakeBody.begin();
    mBodyRect.setFillColor(sf::Color::Black);
    mBodyRect.setPosition(head->position.x * mSize, head->position.y * mSize);
    window.draw(mBodyRect);

    // Draw body
    mBodyRect.setFillColor(sf::Color(80, 120, 80));
    for (auto itr = mSnakeBody.begin() + 1; itr != mSnakeBody.end(); ++itr)
    {
        mBodyRect.setPosition(itr->position.x * mSize, itr->position.y * mSize);
        window.draw(mBodyRect);
    }
}