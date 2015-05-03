#include "Menu.h"

Menu::Menu(std::string backgroundImagePath,
	std::string menuMusicPath,
	std::string buttonImagePath,
	std::string selectedImagePath,
	sf::Vector2u resolution)
{
	backgroundImage.load(backgroundImagePath);
	backgroundImage.setSize();

	if (!musicHandle.openFromFile(menuMusicPath))
		throw FileLoadException(menuMusicPath);
	musicHandle.setLoop(true);

	selectedImage.load(selectedImagePath);

	setupButtons(buttonImagePath, resolution);
	selectButton(MAIN_MENU, 0);
}

void Menu::runFrame(BananaMadness::GameState& gameState, std::vector<unsigned> pressedKeys)
{
	if (musicHandle.getStatus() != sf::Music::Status::Playing)
		musicHandle.play();

	handleInput(gameState, pressedKeys);
	if (gameState == BananaMadness::GameState::IN_MENU)
	{
		backgroundImage.render();
	} else {
		selectedMenu = PAUSED_MENU;
	}
	selectedImage.render();
	for (auto& btn : buttons[selectedMenu])
		btn->render();
}

void Menu::setupButtons(std::string buttonImage, sf::Vector2u resolution)
{
	Button::loadStatics(BUTTON_CLICK_SOUND, BUTTON_HOVER_SOUND, BUTTON_FONT);
	buttons[0].push_back(std::make_unique<Button>(buttonImage, "PLAY"));
	auto& refBtn = *buttons[0][0]; // only the background image will be copied from the reference

	buttons[0].push_back(std::make_unique<Button>(refBtn, "HELP"));
	buttons[0].push_back(std::make_unique<Button>(refBtn, "QUIT"));

	buttons[1].push_back(std::make_unique<Button>(refBtn, "NEW GAME"));
	buttons[1].push_back(std::make_unique<Button>(refBtn, "LOAD GAME"));
	buttons[1].push_back(std::make_unique<Button>(refBtn, "BACK"));

	buttons[2].push_back(std::make_unique<Button>(refBtn, "RESUME"));
	buttons[2].push_back(std::make_unique<Button>(refBtn, "TO MENU"));
	buttons[2].push_back(std::make_unique<Button>(refBtn, "QUIT"));

	unsigned x = unsigned(resolution.x / 2.f - refBtn.getSize().x / 2.f);
	unsigned y_tmp = unsigned(resolution.y / 2.f);
	for (auto& sub_menu : buttons)
		for (unsigned i = 0; i < sub_menu.size(); i++)
		{
			float offset = sub_menu.size() / 2.f - i * 1.1f;
			sub_menu[i]->setPosition({ x, unsigned(y_tmp - offset * refBtn.getSize().y) });
		}
}

void Menu::selectButton(MenuState state, unsigned buttonIndex)
{
	selectedMenu = state;
	selectedButton = buttonIndex;
	auto& imgSize = selectedImage.getSize();
	auto& btnPos = buttons[selectedMenu][selectedButton]->getPosition();
	auto& btnSize = buttons[selectedMenu][selectedButton]->getSize();
	selectedImage.setPosition({ btnPos.x - imgSize.x, unsigned(btnPos.y - btnSize.y / 2.f) });
}

void Menu::handleInput(BananaMadness::GameState& gameState, std::vector<unsigned> pressedKeys)
{
	for (auto& key : pressedKeys)
	{
		switch (key)
		{
		case sf::Keyboard::Return:
			clickButton(gameState);
			break;
		case sf::Keyboard::Escape:
			switch (selectedMenu)
			{
			case Menu::MAIN_MENU:
				exit(EXIT_SUCCESS);
				break;
			case Menu::PLAY_MENU:
				selectButton(MAIN_MENU, 0);
				break;
			case Menu::PAUSED_MENU:
				gameState = BananaMadness::GameState::IN_GAME;
				break;
			}
			break;
		case sf::Keyboard::Up:
			Button::playHoverSound();
			selectButton(selectedMenu, selectedButton == 0 ? buttons[selectedMenu].size() - 1 : selectedButton - 1);
			break;
		case sf::Keyboard::Down:
			Button::playHoverSound();
			selectButton(selectedMenu, selectedButton == buttons[selectedMenu].size() - 1 ? 0 : selectedButton + 1);
			break;
		}
	}
}

void Menu::clickButton(BananaMadness::GameState& gameState)
{
	switch (selectedMenu)
	{
	case Menu::MAIN_MENU:
		switch (selectedButton)
		{
		case 0: // play
			selectButton(PLAY_MENU, 0);
			break;
		case 1: // help
			break;
		case 2: // quit
			exit(EXIT_SUCCESS);
			break;
		}
		break;
	case Menu::PLAY_MENU:
		switch (selectedButton)
		{
		case 0: // new game
			break;
		case 1: // load game
			break;
		case 2: // back
			selectButton(MAIN_MENU, 0);
			break;
		}
		break;
	case Menu::PAUSED_MENU:
		switch (selectedButton)
		{
		case 0: // resume
			break;
		case 1: // to menu
			break;
		case 2: // quit
			break;
		}
		break;
	}
	Button::playClickSound();
}
