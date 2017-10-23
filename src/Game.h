#pragma once
#include "Window.h"
#include "World.h"
#include "Textbox.h"

class Game {

public:
    const Window& getWindow() const;
    sf::Time getElapsed() const;    

    /// Start game
    Game();

    /// End game
    ~Game();
    
    /// Manage player's inputs
    void handleInput();

    /// Frame update
    void update();

    /// Draw game
    void render();

    /// Restart time clock
    void restartClock();


private:
    Window mWindow;
    sf::Clock mClock;
    float mElapsed;
    int mHiScore;
    sf::RectangleShape mBackground;

    World mWorld;
    Snake mSnake;
    Textbox mTextbox;
	PointDisplay mPointDisplay;
};