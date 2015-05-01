#pragma once

#include "Defines.h"
#include "Drawable.h"
#include "Intro.h"
#include <SFML/Graphics.hpp>



class GameManager
{
public:
	enum GameState { IN_INTRO, LOADING, IN_MENU, IN_GAME, PAUSED };

	GameManager(sf::Vector2u resolution, bool fullscreen);
	~GameManager();

	void pollEvents();
	void render();
	bool isRunning();
private:
	void renderGameState();

	sf::RenderWindow windowHandle;
	GameState gameState;
	Intro* intro;
};

