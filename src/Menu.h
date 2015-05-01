#pragma once

#include <vector>
#include <SFML/Audio.hpp>
#include "Drawable.h"
#include "Button.h"

class Menu
{
public:
	Menu(std::string backgroundImagePath);
	void render();
private:
	sf::Music musicHandle;
	Drawable* backgroundImage;
	std::vector<Button*> mainMenuButtons;
	std::vector<Button*> playMenuButtons;
};

