#pragma once

#include <vector>
#include <memory>
#include <SFML/Audio.hpp>
#include <windows.h>

#include <src/menu/Button.h>
#include <src/map/Level.h>

class Menu
{
public:
	Menu(sf::RenderWindow& windowHandle);
	void runFrame(BananaMadness::GameState& gameState, std::vector<unsigned> pressedKeys, Level& mapHandle);
private:
	using ButtonArray = std::vector < std::unique_ptr<Button> > ;
	enum MenuState { MAIN_MENU, PLAY_MENU, PAUSED_MENU, GAME_OVER_MENU, LEVEL_CLEARED_MENU, MENU_ITEMS };

	void setupButtons(std::string buttonImage, sf::Vector2u resolution);
	void handleInput(BananaMadness::GameState& gameState, std::vector<unsigned> pressedKeys, Level& mapHandle);
	void selectButton(MenuState state, unsigned buttonIndex, bool playSound = false);
	void clickButton(BananaMadness::GameState& gameState, Level& mapHandle);

	sf::RenderWindow* windowHandle;
	sf::View menuView;
	sf::Font headerFont;
	sf::Text headerText;
	MenuState selectedMenu;
	unsigned selectedButton;
	sf::Music musicHandle;
	Drawable backgroundImage;
	Drawable selectedImage;
	sf::RectangleShape curtain;
	ButtonArray buttons[MENU_ITEMS];
};
