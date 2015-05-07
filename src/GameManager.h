#pragma once

#include "Defines.h"
#include "Drawable.h"
#include "Intro.h"
#include "Menu.h"
#include <SFML/Graphics.hpp>


class GameManager
{
public:
	GameManager(sf::Vector2u resolution, bool fullscreen);

	void runFrame();
	bool isRunning();
private:
	void renderGameState();

	sf::RenderWindow windowHandle;
	BananaMadness::GameState gameState;
 	Intro* intro;
 	Menu* menu;
};

