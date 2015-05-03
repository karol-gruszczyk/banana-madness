#pragma once

#include <vector>
#include <memory>
#include <SFML/Audio.hpp>
#include "Defines.h"
#include "Button.h"

class Menu
{
public:
	Menu(std::string backgroundImagePath, std::string menuMusic, std::string buttonImage, std::string selectedImage, sf::Vector2u resolution);
	void runFrame(BananaMadness::GameState& gameState, std::vector<unsigned> pressedKeys);
	void handleInput(BananaMadness::GameState& gameState, std::vector<unsigned> pressedKeys);
private:
	using ButtonArray = std::vector < std::unique_ptr<Button> > ;
	enum MenuState { MAIN_MENU, PLAY_MENU, PAUSED_MENU };

	void setupButtons(std::string buttonImage, sf::Vector2u resolution);
	void selectButton(MenuState state, unsigned buttonIndex);
	void clickButton(BananaMadness::GameState& gameState);

	MenuState selectedMenu;
	unsigned selectedButton;
	sf::Music musicHandle;
	Drawable backgroundImage;
	Drawable selectedImage;
	ButtonArray buttons[3];
};
