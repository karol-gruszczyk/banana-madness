#pragma once

#include "Defines.h"
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
	sf::RenderWindow windowHandle;
};

