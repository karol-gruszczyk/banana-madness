#pragma once

#include <vector>
#include <memory>
#include <SFML/Audio.hpp>
#include "Header.h"
#include "Button.h"

class Menu
{
public:
	Menu(std::string backgroundImagePath, std::string buttonImage);
	void render(BananaMadness::GameState& gameState);

private:
	using ButtonArray = std::vector < std::unique_ptr<Button> > ;

	sf::Music musicHandle;
	Drawable backgroundImage;
	ButtonArray mainMenuButtons;
	ButtonArray playMenuButtons;
};

