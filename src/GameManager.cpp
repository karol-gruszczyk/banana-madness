#include "GameManager.h"


GameManager::GameManager(sf::Vector2u resolution, bool fullscreen)
{
	windowHandle.create(sf::VideoMode(resolution.x, resolution.y), 
						WINDOW_TITLE, 
						fullscreen ? sf::Style::Fullscreen : sf::Style::Close);
	Drawable::windowHandle = &windowHandle;
	gameState = INITIAL_GAME_STATE;
	intro = new Intro(INTRO_MUSIC);
	menu = new Menu(MENU_BACKGROUND, BUTTON_IMAGE, BUTTON_SELECTED_IMAGE, resolution);
}

void GameManager::runFrame()
{
	windowHandle.clear();
	renderGameState();
	windowHandle.display();
}

bool GameManager::isRunning()
{
	return windowHandle.isOpen();
}

void GameManager::renderGameState()
{
	sf::Event event;
	std::vector<unsigned> pressedKeys;
	std::vector<unsigned> releasedKeys;
	while (windowHandle.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			windowHandle.close();
		else if (event.type == sf::Event::KeyPressed)
			pressedKeys.push_back(event.key.code);
		else if (event.type == sf::Event::KeyReleased)
			releasedKeys.push_back(event.key.code);
	}
	switch (gameState)
	{
	case BananaMadness::GameState::IN_INTRO:
		intro->runFrame(gameState, releasedKeys);
		break;
	case BananaMadness::GameState::LOADING:
		// not sure if needed
		break;
	case BananaMadness::GameState::IN_MENU:
		menu->runFrame(gameState, releasedKeys);
		break;
	case BananaMadness::GameState::IN_GAME:
		// render game
		break;
	case BananaMadness::GameState::PAUSED:
		// render game
		menu->runFrame(gameState, releasedKeys);
		break;
	}
}
