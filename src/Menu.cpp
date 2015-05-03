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
	buttons[0].push_back(std::unique_ptr<Button>(new Button(buttonImage, "PLAY")));
	auto& refBtn = *buttons[0][0];
	unsigned x = unsigned(resolution.x / 2.f - refBtn.getSize().x / 2.f);
	unsigned y = unsigned(resolution.y / 2.f);
	auto xy = [](unsigned x, unsigned y, Button btn, float off) ->sf::Vector2u { return{ x, unsigned(y - off * btn.getSize().y) }; };
	refBtn.setPosition(xy(x, y, refBtn, 1.6f));

	buttons[0].push_back(std::unique_ptr<Button>(new Button(refBtn, "HELP", xy(x, y, refBtn, .5f))));
	buttons[0].push_back(std::unique_ptr<Button>(new Button(refBtn, "QUIT", xy(x, y, refBtn, -.6f))));

	buttons[1].push_back(std::unique_ptr<Button>(new Button(refBtn, "NEW GAME", xy(x, y, refBtn, 1.6f))));
	buttons[1].push_back(std::unique_ptr<Button>(new Button(refBtn, "LOAD GAME", xy(x, y, refBtn, .5f))));
	buttons[1].push_back(std::unique_ptr<Button>(new Button(refBtn, "BACK", xy(x, y, refBtn, -.6f))));

	buttons[2].push_back(std::unique_ptr<Button>(new Button(refBtn, "RESUME", xy(x, y, refBtn, 1.6f))));
	buttons[2].push_back(std::unique_ptr<Button>(new Button(refBtn, "TO MENU", xy(x, y, refBtn, .5f))));
	buttons[2].push_back(std::unique_ptr<Button>(new Button(refBtn, "QUIT", xy(x, y, refBtn, -.6f))));
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
			selectButton(selectedMenu, selectedButton == 0 ? buttons[selectedMenu].size() - 1 : selectedButton - 1);
			break;
		case sf::Keyboard::Down:
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
}
