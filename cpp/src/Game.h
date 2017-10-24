#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
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
	sf::Music mMusic;
	sf::SoundBuffer mSoundTurn;
	sf::SoundBuffer mSoundCollision;
	sf::SoundBuffer mSoundHiScore;
	sf::Sound mSound;

    World mWorld;
    Snake mSnake;
    Textbox mTextbox;
	PointDisplay mPointDisplay;

	/// Play sound when player turns
	void playTurnSound();
};