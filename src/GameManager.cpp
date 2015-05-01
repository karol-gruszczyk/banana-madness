#include "GameManager.h"


GameManager::GameManager(sf::Vector2u resolution, bool fullscreen)
{
	windowHandle.create(
		sf::VideoMode(resolution.x, resolution.y), 
		WINDOW_TITLE, 
		fullscreen ? sf::Style::Fullscreen : sf::Style::Default
		);
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

	windowHandle.display();
}

bool GameManager::isRunning()
{
	return windowHandle.isOpen();
}
