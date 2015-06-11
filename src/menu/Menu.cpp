#include "Menu.h"

Menu::Menu(sf::RenderWindow& windowHandle) : windowHandle(&windowHandle)
{
	menuView = sf::View(sf::FloatRect(0.f, 0.f, (float)windowHandle.getSize().x, (float)windowHandle.getSize().y));

	backgroundImage.load(MENU_BACKGROUND_PATH);
	backgroundImage.setSize();

	if (!musicHandle.openFromFile(MENU_MUSIC_PATH))
		throw FileLoadException(MENU_MUSIC_PATH);
	musicHandle.setLoop(true);

	selectedImage.load(BUTTON_SELECTED_IMAGE_PATH);

	setupButtons(BUTTON_IMAGE_PATH, windowHandle.getSize());
	selectButton(MAIN_MENU, 0);

	curtain.setSize((sf::Vector2f)windowHandle.getSize());
	curtain.setFillColor(sf::Color(0, 0, 0, 200));

	if (!headerFont.loadFromFile(HEADER_FONT_PATH))
		throw FileLoadException(HEADER_FONT_PATH);
	headerText.setFont(headerFont);
	headerText.setColor(sf::Color::White);
	headerText.setCharacterSize(100);
}

void Menu::runFrame(BananaMadness::GameState& gameState, std::vector<unsigned> pressedKeys, Level& mapHandle)
{
	windowHandle->setView(menuView);
	if (musicHandle.getStatus() != sf::Music::Status::Playing && gameState == BananaMadness::GameState::IN_MENU)
		musicHandle.play();

	handleInput(gameState, pressedKeys, mapHandle);
	if (gameState == BananaMadness::GameState::IN_MENU)
	{
		backgroundImage.render();
	} else {
		windowHandle->draw(curtain);
		if (gameState == BananaMadness::GameState::PAUSED)
		{
			if (selectedMenu != PAUSED_MENU)
				selectButton(PAUSED_MENU, 0);
			headerText.setString("PAUSED");
		}
		else if (gameState == BananaMadness::GameState::GAME_OVER)
		{
			if (selectedMenu != GAME_OVER_MENU)
				selectButton(GAME_OVER_MENU, 0);
			headerText.setString("GAME OVER");
		}
		else if (gameState == BananaMadness::GameState::LEVEL_CLEARED)
		{
			if (selectedMenu != LEVEL_CLEARED_MENU)
				selectButton(LEVEL_CLEARED_MENU, 0);
			headerText.setString("LEVEL CLEARED");
		}
		windowHandle->draw(headerText);
		headerText.setPosition(windowHandle->getSize().x / 2.f - headerText.getLocalBounds().width / 2.f,
							   .05f * windowHandle->getSize().y);
	}
	selectedImage.render();
	for (auto& btn : buttons[selectedMenu])
		btn->render();
}

void Menu::setupButtons(std::string buttonImage, sf::Vector2u resolution)
{
	buttons[MAIN_MENU].push_back(std::make_unique<Button>(buttonImage, BUTTON_HOVER_SOUND, BUTTON_CLICK_SOUND, BUTTON_FONT, "NEW GAME"));
	auto& refBtn = *buttons[0][0]; // only the background image will be copied from the reference
	buttons[MAIN_MENU].push_back(std::make_unique<Button>(refBtn, "ABOUT"));
	buttons[MAIN_MENU].push_back(std::make_unique<Button>(refBtn, "QUIT"));

	buttons[PLAY_MENU].push_back(std::make_unique<Button>(refBtn, "EASY"));
	buttons[PLAY_MENU].push_back(std::make_unique<Button>(refBtn, "EXTREMELY HARD"));
	buttons[PLAY_MENU].push_back(std::make_unique<Button>(refBtn, "BACK"));

	buttons[PAUSED_MENU].push_back(std::make_unique<Button>(refBtn, "RESUME"));
	buttons[PAUSED_MENU].push_back(std::make_unique<Button>(refBtn, "TO MENU"));
	buttons[PAUSED_MENU].push_back(std::make_unique<Button>(refBtn, "QUIT"));

	buttons[GAME_OVER_MENU].push_back(std::make_unique<Button>(refBtn, "REPLAY"));

	buttons[LEVEL_CLEARED_MENU].push_back(std::make_unique<Button>(refBtn, "REPLAY"));
	buttons[LEVEL_CLEARED_MENU].push_back(std::make_unique<Button>(refBtn, "NEXT LEVEL"));

	unsigned x = unsigned(resolution.x / 2.f - refBtn.getSize().x / 2.f);
	unsigned y_tmp = unsigned(resolution.y / 2.f);
	for (auto& sub_menu : buttons)
		for (unsigned i = 0; i < sub_menu.size(); i++)
		{
			float offset = sub_menu.size() / 2.f - i * 1.1f;
			sub_menu[i]->setPosition({ (float)x, y_tmp - offset * refBtn.getSize().y });
		}
}

void Menu::selectButton(MenuState state, unsigned buttonIndex, bool playSound /* = false */)
{
	if (playSound)
		buttons[selectedMenu][selectedButton]->playHoverSound();
	selectedMenu = state;
	selectedButton = buttonIndex;
	auto& imgSize = selectedImage.getSize();
	auto& btnPos = buttons[selectedMenu][selectedButton]->getPosition();
	auto& btnSize = buttons[selectedMenu][selectedButton]->getSize();
	selectedImage.setPosition({ (float)btnPos.x - imgSize.x, btnPos.y - btnSize.y / 2.f });
}

void Menu::handleInput(BananaMadness::GameState& gameState, std::vector<unsigned> pressedKeys, Level& mapHandle)
{
	for (auto& key : pressedKeys)
	{
		switch (key)
		{
		case sf::Keyboard::Return:
			clickButton(gameState, mapHandle);
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
			selectButton(selectedMenu, selectedButton == 0 ? buttons[selectedMenu].size() - 1 : selectedButton - 1, true);
			break;
		case sf::Keyboard::Down:
			selectButton(selectedMenu, selectedButton == buttons[selectedMenu].size() - 1 ? 0 : selectedButton + 1, true);
			break;
		}
	}
}

void Menu::clickButton(BananaMadness::GameState& gameState, Level& mapHandle)
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
		case 0: // easy
			//open some shit
			ShellExecute(0, 0, EASY_GAME_URL, 0, 0, SW_SHOW);
			break;
		case 1: // extremely hard
			musicHandle.stop();
			mapHandle.loadLevel(INITIAL_LEVEL);
			gameState = BananaMadness::IN_GAME;
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
			gameState = BananaMadness::IN_GAME;
			break;
		case 1: // to menu
			gameState = BananaMadness::IN_MENU;
			selectButton(Menu::MAIN_MENU, 0);
			break;
		case 2: // quit
			exit(EXIT_SUCCESS);
			break;
		}
		break;
	case Menu::GAME_OVER_MENU: //replay
		musicHandle.stop();
		mapHandle.reloadLevel();
		gameState = BananaMadness::IN_GAME;
		break;
	case Menu::LEVEL_CLEARED_MENU:
		switch (selectedButton)
		{
		case 0: // replay
			mapHandle.reloadLevel();
			break;
		case 1: // next level
			auto levelId = mapHandle.getCurrentLevel() + 1;
			if (levelId >= NUM_LEVELS)
				levelId = 0;
			mapHandle.loadLevel(levelId);
			break;
		}
		gameState = BananaMadness::IN_GAME;
		musicHandle.stop();
		break;
	}
	buttons[selectedMenu][selectedButton]->playClickSound();
}
