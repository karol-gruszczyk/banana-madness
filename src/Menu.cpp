#include "Menu.h"



Menu::Menu(std::string backgroundImagePath, std::string buttonImage)
{
	backgroundImage.load(backgroundImagePath);
	backgroundImage.setSize();

	mainMenuButtons.push_back(std::unique_ptr<Button>(new Button(buttonImage, "PLAY", nullptr)));
	auto& refBtn = *mainMenuButtons[0];
	mainMenuButtons.push_back(std::unique_ptr<Button>(new Button(refBtn, "HELP", nullptr)));
	mainMenuButtons.push_back(std::unique_ptr<Button>(new Button(refBtn, "QUIT", nullptr)));

	playMenuButtons.push_back(std::unique_ptr<Button>(new Button(refBtn, "NEW GAME", nullptr)));
	playMenuButtons.push_back(std::unique_ptr<Button>(new Button(refBtn, "LOAD GAME", nullptr)));
	playMenuButtons.push_back(std::unique_ptr<Button>(new Button(refBtn, "BACK", nullptr)));
}

void Menu::render(BananaMadness::GameState& gameState)
{
	backgroundImage.render();
}
