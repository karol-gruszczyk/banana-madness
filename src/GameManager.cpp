#include "GameManager.h"


GameManager::GameManager(sf::Vector2u resolution, bool fullscreen)
{
	windowHandle.create(sf::VideoMode(resolution.x, resolution.y), 
						WINDOW_TITLE, 
						fullscreen ? sf::Style::Fullscreen : sf::Style::Close);
	windowHandle.setPosition({ 0, 0 });
	Drawable::windowHandle = &windowHandle;
	gameState = INITIAL_GAME_STATE;
	intro = std::make_unique<Intro>(INTRO_VIDEO);
	menu = std::make_unique<Menu>(MENU_BACKGROUND, MENU_MUSIC, BUTTON_IMAGE, BUTTON_SELECTED_IMAGE, PLAY_SOUND, windowHandle);
	map = std::make_unique<Level>(windowHandle);
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
			closeWindow();
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
		menu->runFrame(gameState, releasedKeys, *map);
		break;
	case BananaMadness::GameState::IN_GAME:
		map->runFrame(gameState, pressedKeys, releasedKeys);
		break;
	case BananaMadness::GameState::PAUSED:
		map->runFrame(gameState, pressedKeys, releasedKeys);
		menu->runFrame(gameState, releasedKeys, *map);
		break;
	}
}

void GameManager::closeWindow()
{
	if (gameState == BananaMadness::GameState::IN_INTRO)
		intro->stopVideo();
	exit(EXIT_SUCCESS); // TODO
}
