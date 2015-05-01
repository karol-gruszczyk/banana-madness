#include "GameManager.h"


GameManager::GameManager(sf::Vector2u resolution, bool fullscreen)
{
	windowHandle.create(sf::VideoMode(resolution.x, resolution.y), 
						WINDOW_TITLE, 
						fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	Drawable::windowHandle = &windowHandle;
	gameState = GameState::IN_INTRO;
	intro = new Intro("data/sound/intro.wav");
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
	case IN_INTRO:
		if (intro->render(windowHandle))
			gameState = GameManager::GameState::IN_MENU;
		break;
	case LOADING:
		break;
	case IN_MENU:
		break;
	case IN_GAME:
		break;
	case PAUSED:
		break;
	}
}
