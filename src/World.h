#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Constants.h"
#include "Apple.h"

class World
{
public:
  World(sf::Vector2u windowSize, Snake& player);
  ~World();

  int getBlockSize();

  /// Update
  void update(Snake &player);

  /// Make an apple appear
  void respawnApple(Snake& player);

  /// Reset world when player lose
  void reset(Snake& player);

  /// Draw world in window
  void render(sf::RenderWindow &window);

private:
  sf::Vector2u mWindowSize;
  int mBlockSize;
  Apple mApple;
  sf::RectangleShape mBounds[4];
};