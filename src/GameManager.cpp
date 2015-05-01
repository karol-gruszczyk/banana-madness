#include "GameManager.h"


GameManager::GameManager(sf::Vector2u resolution, bool fullscreen)
{
	windowHandle.create(sf::VideoMode(resolution.x, resolution.y), 
						WINDOW_TITLE, 
						fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	Drawable::windowHandle = &windowHandle;
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
	//rendering items
	windowHandle.display();
}

bool GameManager::isRunning()
{
	return windowHandle.isOpen();
}
