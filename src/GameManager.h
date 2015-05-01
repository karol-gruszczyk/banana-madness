#pragma once

#include "Defines.h"
#include "Header.h"
#include "Drawable.h"
#include "Intro.h"
#include "Menu.h"
#include <SFML/Graphics.hpp>


class GameManager
{
public:
	GameManager(sf::Vector2u resolution, bool fullscreen);
	~GameManager();

	void pollEvents();
	void render();
	bool isRunning();
private:
	void renderGameState();

	sf::RenderWindow windowHandle;
	BananaMadness::GameState gameState;
 	Intro* intro;
 	Menu* menu;
};

