#pragma once

#include <SFML/Graphics.hpp>

#include <src/Globals.h>
#include <src/base/Drawable.h>
#include <src/menu/Menu.h>
#include <src/menu/Intro.h>
#include <src/map/Map.h>


class GameManager
{
public:
	GameManager(sf::Vector2u resolution, bool fullscreen);

	void runFrame();
	bool isRunning();
private:
	void renderGameState();
	void closeWindow();
	sf::RenderWindow windowHandle;
	BananaMadness::GameState gameState;
 	std::unique_ptr<Intro> intro;
	std::unique_ptr<Menu> menu;
	std::unique_ptr<Map> map;
};

