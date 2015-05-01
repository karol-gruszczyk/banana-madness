#include "Menu.h"



Menu::Menu(std::string backgroundImagePath, std::string buttonImage)
{
	backgroundImage.load(backgroundImagePath);
	backgroundImage.setSize();

	mainMenuButtons.push_back(std::unique_ptr<Button>(new Button(buttonImage, "PLAY", nullptr)));
	auto& button = mainMenuButtons[0];
 	mainMenuButtons.push_back(std::unique_ptr<Button>(new Button(*button, "HELP", nullptr)));
//	The application crashes with an "memory access violation" exception after creating a third instance of button texture
// 	mainMenuButtons.push_back(std::unique_ptr<Button>(new Button(*button, "QUIT", nullptr)));

// 	playMenuButtons.push_back(std::unique_ptr<Button>(new Button(*button, "NEW GAME", nullptr)));
// 	playMenuButtons.push_back(std::unique_ptr<Button>(new Button(*button, "LOAD GAME", nullptr)));
// 	playMenuButtons.push_back(std::unique_ptr<Button>(new Button(*button, "BACK", nullptr)));
}

void Menu::render(BananaMadness::GameState& gameState)
{
	backgroundImage.render();
}
