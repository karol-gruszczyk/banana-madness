#include "Menu.h"



Menu::Menu(std::string backgroundImagePath)
{
	backgroundImage = new Drawable(backgroundImagePath);
	mainMenuButtons.push_back(new Button("PLAY"));
	mainMenuButtons.push_back(new Button("HELP"));
	mainMenuButtons.push_back(new Button("QUIT"));

	playMenuButtons.push_back(new Button("NEW GAME"));
	playMenuButtons.push_back(new Button("LOAD GAME"));
	playMenuButtons.push_back(new Button("BACK"));
}
