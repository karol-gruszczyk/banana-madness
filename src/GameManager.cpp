#include "GameManager.h"


GameManager::GameManager(sf::Vector2u resolution, bool fullscreen)
{
	windowHandle.create(sf::VideoMode(resolution.x, resolution.y), 
						WINDOW_TITLE, 
						fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	Drawable::windowHandle = &windowHandle;
	gameState = INITIAL_GAME_STATE;
	intro = new Intro(INTRO_MUSIC);
	menu = new Menu(MENU_BACKGROUND, BUTTON_IMAGE);
}

GameManager::~GameManager()
{
}

void GameManager::pollEvents()
{
	sf::Event event;
	while (windowHandle.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			windowHandle.close();
	}
}

void GameManager::render()
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
	switch (gameState)
	{
	case BananaMadness::GameState::IN_INTRO:
		intro->render(gameState);
		break;
	case BananaMadness::GameState::LOADING:
		break;
	case BananaMadness::GameState::IN_MENU:
		menu->render(gameState);
		break;
	case BananaMadness::GameState::IN_GAME:
		break;
	case BananaMadness::GameState::PAUSED:
		break;
	}
}
